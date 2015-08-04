/*
 *  Copyright (C) 2015  Andrei Karas
 *
 *  This file is part of Paranoid null checker.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "analysis/reports.h"

#include "command.h"
#include "logger.h"

#include "analysis/analysis.h"
#include "analysis/expression.h"
#include "analysis/varitem.h"
#include "analysis/walkitem.h"

#include "nodes/base/node.h"

#include "nodes/decl/parm_decl.h"
#include "nodes/decl/var_decl.h"

#include "localconsts.h"

namespace Analysis
{

// check is var from node can be checked for null pointer
bool checkForReport(Node *node,
                    const WalkItem &wi)
{
    node = skipNop(node);
    return node &&
        (node == PARM_DECL || node == VAR_DECL) &&
        isIn(node->label, wi.needCheckNullVars);
}

// report about useless check for null pointer
void reportUselessCheck(Node *node,
                        const std::string &var)
{
    if (!checkCommand(DetectUseless))
        return;
    Log::warn(findBackLocation(node),
        "Useless variable check '%s'. It already was checked before",
        var);
}

// report about null pointer if need for node
void reportParmDeclNullPointer(Node *mainNode,
                               Node *node,
                               const WalkItem &wi)
{
    node = skipNop(node);
    if (node)
    {
        if (!node->label.empty())
        {
            if (node == PARM_DECL)
            {
                ParmDeclNode *parmDecl = static_cast<ParmDeclNode*>(node);
                if (parmDecl->declType == POINTER_TYPE &&
                    isIn(node->label, wi.needCheckNullVars))
                {
                    Log::warn(findBackLocation(mainNode),
                        "Using parameter '%s' without checking for null pointer",
                        node->label);
                }
            }
            else if (node == VAR_DECL)
            {
                VarDeclNode *varDecl = static_cast<VarDeclNode*>(node);
                if (varDecl->varType == POINTER_TYPE &&
                    isIn(node->label, wi.needCheckNullVars))
                {
                    Log::warn(findBackLocation(mainNode),
                        "Using variable '%s' without checking for null pointer",
                        node->label);
                }
            }
        }
        else if (node == COMPONENT_REF)
        {
            auto vars = getComponentRefParts(node);
            FOR_EACH (var, vars)
            {
                if (isIn(var.name, wi.needCheckNullVars) ||
                    isNotIn(var.name, wi.knownVars))
                {
                    Log::warn(findBackLocation(mainNode),
                        "Using variable '%s' without checking for null pointer",
                        var.name);
                }
            }
        }
    }
}

// report about null pointer if need for node
void reportParmDeclLeftNullPointer(Node *mainNode,
                                   Node *node,
                                   const WalkItem &wi)
{
    node = skipNop(node);
    if (node)
    {
        if (node == COMPONENT_REF)
        {
            auto vars = getComponentRefLeftParts(node);
            FOR_EACH (var, vars)
            {
                if (isIn(var.name, wi.needCheckNullVars))
                {
                    Log::warn(findBackLocation(mainNode),
                        "Using field '%s' without checking for null pointer",
                        var.name);
                }
            }
        }
    }
}

// report about null pointer if need for node
void reportComponentRefNullPointer(Node *mainNode,
                                   Node *node,
                                   const WalkItem &wi)
{
    node = skipNop(node);
    if (node)
    {
        if (node == COMPONENT_REF)
        {
            auto vars = getComponentRefParts(node);
            FOR_EACH (var, vars)
            {
                if (isIn(var.name, wi.needCheckNullVars))
                {
                    Log::warn(findBackLocation(mainNode),
                        "Using field '%s' without checking for null pointer",
                        var.name);
                }
            }
        }
    }
}

void reportPossibleNullPointer(Node *node,
                               const std::string &label)
{
    Log::warn(findBackLocation(node),
        "warning: possible null argument '%s' where non-null required",
        label);
}

void reportParmDeclAttrNullPointer(Node *mainNode,
                                   Node *node,
                                   const WalkItem &wi)
{
    node = skipNop(node);
    if (node)
    {
        if (!node->label.empty())
        {
            if (node == PARM_DECL)
            {
                if (isIn(node->label, wi.needCheckNullVars))
                    reportPossibleNullPointer(mainNode, node->label);
            }
            else if (node == VAR_DECL)
            {
                if (isIn(node->label, wi.needCheckNullVars))
                    reportPossibleNullPointer(mainNode, node->label);
            }
        }
        else if (node == COMPONENT_REF)
        {
            VarItem var = getComponentRefVariable(node);
            if (isIn(var.name, wi.needCheckNullVars))
                reportPossibleNullPointer(mainNode, node->label);
        }
    }
}

void reportWrongCheck(Node *node)
{
    Log::warn(findBackLocation(node),
        "warning: wrong call to internal debug function. Three arguments required",
        "");
}

void reportCollectionsDifferent(Node *node,
                                const std::string &name,
                                std::string str1,
                                std::string str2)
{
    std::string str = "internal collections '%s' is different.\nwant: " +
        str2 +
        "\n get: " +
        str1;
    Log::warn(findBackLocation(node),
        str,
        name);
}

}
