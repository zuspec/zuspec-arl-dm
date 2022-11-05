The activity model serves several purpose, with the end goal of providing
a data structure that can be evaluated to execute the schedule.

The activity model starts off as a nearly-verbatim transcription of the 
type data structure.
- Traversal is a leaf node
  - Has sub-scope for compound
  - No sub-scope for atomic
- Sequence, parallel, schedule represented as a scope with a kind
  - List of child handles
  - List of 
- ? How to deal with behavioral scopes ?

Each activity has two optional references: next sequential, and next parallel

# Type vs Model
The type model is quite literal. If there are multiple activities within an 
action, there will be multiple activity-type fields in the type model. To
simplify one aspect of model interpretation, the implied 'schedule' is 
inserted during construction of the model.

# Model mutation
The initial model is suitable when activities are explicit, and schedule
is not used. All manipulation assumes that the root data structure is a 
scope, so the root action must be enclosed in one.

# Lifecycle
The original activity view is structural and mirrors that captured in the
type model.

