
Each action has one or more component contexts with which it can be associated.
- If the action is started explicitly, those contexts must be within the the
  context associated with the containing action.
- If the action is started implicitly, those contexts must be within the
  context associated with the pool that created the action.

Each action claim is associated with a pool based on its component association.
The component context / pool for all references and the action itself must match.

In order for two actions to share a flow object
- All must point to the same pool
- Constraints must agree

Each flow object holds a 'pool-id' attribute. 