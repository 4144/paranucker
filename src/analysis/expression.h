/*
 *  Copyright (C) 2015  Andrei Karas
 *
 *  This file is part of AstDumper.
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

#ifndef ANALYSIS_EXPRESSION_H
#define ANALYSIS_EXPRESSION_H

#include "includes.h"

struct AddrExprNode;
struct BindExprNode;
struct CompoundExprNode;
struct CondExprNode;
struct DeclExprNode;
struct EqExprNode;
struct ModifyExprNode;
struct NeExprNode;
struct PointerPlusExprNode;
struct ReturnExprNode;
struct TruthAndIfExprNode;
struct TruthOrIfExprNode;
struct WalkItem;

namespace Analysis
{
    void analyseModifyExpr(ModifyExprNode *node, const WalkItem &wi, WalkItem &wo);

    void analysePointerPlusExpr(PointerPlusExprNode *node, const WalkItem &wi, WalkItem &wo);

    void analyseAddrExpr(AddrExprNode *node, const WalkItem &wi, WalkItem &wo);

    void analyseReturnExpr(ReturnExprNode *node, const WalkItem &wi, WalkItem &wo);

    void analyseNeExpr(NeExprNode *node, const WalkItem &wi, WalkItem &wo);

    void analyseEqExpr(EqExprNode *node, const WalkItem &wi, WalkItem &wo);

    void analyseTruthOrIfExpr(TruthOrIfExprNode *node, const WalkItem &wi, WalkItem &wo);

    void analyseTruthAndIfExpr(TruthAndIfExprNode *node, const WalkItem &wi, WalkItem &wo);

    void analyseCondExpr(CondExprNode *node, const WalkItem &wi, WalkItem &wo);

    void analyseCompoundExpr(CompoundExprNode *node, const WalkItem &wi, WalkItem &wo);

    void analyseBindExpr(BindExprNode *node, const WalkItem &wi, WalkItem &wo);

    void analyseDeclExpr(DeclExprNode *node, const WalkItem &wi, WalkItem &wo);
}

#endif // ANALYSIS_EXPRESSION_H
