import pytest
from zsp_arl_dm.core import Factory, Context

def test_activity_sequence():
    # Get factory instance and create context
    factory = Factory.inst()
    context = factory.mkContext()
    
    # Create component and action types first
    comp_type = context.mkDataTypeComponent("MyComponent")
    action_type = context.mkDataTypeAction("MyAction")
    action_type.setComponentType(comp_type)
    
    # Add types to context
    assert context.addDataTypeComponent(comp_type) == True
    assert context.addDataTypeAction(action_type) == True
    
    # Create sequence activity
    seq = context.mkDataTypeActivitySequence()
    assert seq is not None
    
    # Create parallel activity inside sequence
    parallel = context.mkDataTypeActivityParallel()
    assert parallel is not None
    
    # Create two activities in parallel
    seq1 = context.mkDataTypeActivitySequence()
    seq2 = context.mkDataTypeActivitySequence()
    
    # Add sequences to parallel
    parallel.addActivity(context.mkTypeFieldActivity("seq1", seq1, True))
    parallel.addActivity(context.mkTypeFieldActivity("seq2", seq2, True))
    
    # Add parallel to main sequence
    seq.addActivity(context.mkTypeFieldActivity("parallel", parallel, True))
    
    # Verify structure
    activities = seq.getActivities()
    assert len(activities) == 1
    
    parallel_field = activities[0]
    assert parallel_field is not None
    
    parallel_activities = parallel.getActivities()
    assert len(parallel_activities) == 2
    assert parallel_activities[0] is not None
    assert parallel_activities[1] is not None
