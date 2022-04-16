/*
 * Context.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IContext.h"

namespace arl {

class Context : public IContext {
public:
	Context(vsc::IContext *ctxt);

	virtual ~Context();

	virtual vsc::IModelFieldRoot *buildModelField(
			vsc::IDataTypeStruct			*dt,
			const std::string		&name) override;

	virtual vsc::ICompoundSolver *mkCompoundSolver() override;

	virtual vsc::IDataTypeInt *findDataTypeInt(
			bool			is_signed,
			int32_t			width) override;

	/**
	 * Returns a new datatype. The expectation is that
	 * it will be subsequently added to the context
	 */
	virtual vsc::IDataTypeInt *mkDataTypeInt(
			bool			is_signed,
			int32_t			width) override;

	virtual bool addDataTypeInt(vsc::IDataTypeInt *t) override;

	virtual vsc::IDataTypeStruct *findDataTypeStruct(const std::string &name) override;

	virtual vsc::IDataTypeStruct *mkDataTypeStruct(const std::string &name) override;

	virtual bool addDataTypeStruct(vsc::IDataTypeStruct *t) override;

	virtual vsc::IModelConstraintBlock *mkModelConstraintBlock(
			const std::string &name) override;

	virtual vsc::IModelConstraintExpr *mkModelConstraintExpr(
			vsc::IModelExpr		*expr) override;

	virtual vsc::IModelExprBin *mkModelExprBin(
			vsc::IModelExpr		*lhs,
			vsc::BinOp			op,
			vsc::IModelExpr		*rhs) override;

	virtual vsc::IModelExprFieldRef *mkModelExprFieldRef(
			vsc::IModelField		*field) override;

	virtual vsc::IModelExprVal *mkModelExprVal(vsc::IModelVal *) override;

	virtual vsc::IModelFieldRoot *mkModelFieldRoot(
			vsc::IDataType 			*type,
			const std::string	&name) override;

	virtual vsc::IModelFieldType *mkModelFieldType(
			vsc::ITypeField			*type) override;

	virtual vsc::IRandomizer *mkRandomizer(
			vsc::ISolverFactory		*solver_factory,
			vsc::IRandState			*randstate) override;


	virtual vsc::IRandState *mkRandState(uint32_t seed) override;

	virtual vsc::ITask *mkTask(vsc::TaskE id) override;

	virtual vsc::ITypeExprBin *mkTypeExprBin(
			vsc::ITypeExpr		*lhs,
			vsc::BinOp			op,
			vsc::ITypeExpr		*rhs) override;

	virtual vsc::ITypeConstraintBlock *mkTypeConstraintBlock(const std::string &name) override;

	virtual vsc::ITypeConstraintExpr *mkTypeConstraintExpr(vsc::ITypeExpr *) override;

	virtual vsc::ITypeConstraintScope *mkTypeConstraintScope() override;

	virtual vsc::ITypeExprFieldRef *mkTypeExprFieldRef() override;

	virtual vsc::ITypeExprVal *mkTypeExprVal(const vsc::IModelVal *) override;

	virtual vsc::ITypeField *mkTypeField(
			const std::string		&name,
			vsc::IDataType				*dtype,
			vsc::TypeFieldAttr			attr,
			vsc::IModelVal				*init) override;


private:
	vsc::IContext			*m_ctxt;
};

} /* namespace arl */

