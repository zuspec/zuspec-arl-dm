import pytest
from zsp_arl_dm.core import Factory, Context
from vsc_dm.core import ValRef

# def test_activity_replicate():
#     # Get factory instance and create context
#     factory = Factory.inst()
#     context = factory.mkContext()
    
#     # Create component and action types first
#     comp_type = context.mkDataTypeComponent("MyComponent")
#     action_type = context.mkDataTypeAction("MyAction")
#     action_type.setComponentType(comp_type)
    
#     # Add types to context
#     assert context.addDataTypeComponent(comp_type) == True
#     assert context.addDataTypeAction(action_type) == True
    
#     # Create a sequence to repeat
#     seq = context.mkDataTypeActivitySequence()
#     assert seq is not None
    
#     # Create a replicate activity with count=5
#     expr = context.mkTypeExprVal(context.mkValRefInt(5, False, 32))  # Create int value expression as recommended
#     replicate = context.mkDataTypeActivityReplicate(expr)
#     assert replicate is not None
    
#     # Add sequence to replicate
#     replicate.addActivity(context.mkTypeFieldActivity("seq", seq, True))
    
#     # Verify structure
#     activities = replicate.getActivities()
#     assert len(activities) == 1
#     assert activities[0] is not None
    
#     # Verify count expression
#     count_expr = replicate.getCount()
#     assert count_expr is not None
#     assert count_expr.val() == 5
