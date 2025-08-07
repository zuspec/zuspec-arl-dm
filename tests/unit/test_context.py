import pytest
from zsp_arl_dm.core import Factory, Context

def test_context_basic():
    # Get factory instance and create context
    factory = Factory.inst()
    context = factory.mkContext()
    
    # Create a component type first (since actions need a component)
    comp_type = context.mkDataTypeComponent("MyComponent")
    assert comp_type is not None
    
    # Create an action type
    action_type = context.mkDataTypeAction("MyAction")
    assert action_type is not None
    
    # Set up component-action relationship
    action_type.setComponentType(comp_type)
    assert action_type.getComponentType() == comp_type
    
    # Add both types to context
    assert context.addDataTypeComponent(comp_type) == True
    assert context.addDataTypeAction(action_type) == True
    
    # Verify lookup through specific find methods
    assert context.findDataTypeComponent("MyComponent") == comp_type
    assert context.findDataTypeAction("MyAction") == action_type
