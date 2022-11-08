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

# Evaluation process

Expand and perform local scheduling on the way down. Perform final scheduling
on the way back once all sub-scheduling has been resolved.

Prioritize claim/flow object over schedule.

Next step: perform some activity manipulation using replicate

## Handling of Replicate
- Each replicate has a variable corresponding to its size
- Each replicate has a variable corresponding to the current iteration

Note: replicate unrolling must occur before evaluation of the activity
statements.

- When processing the activities inside a compound action, the value of
  the replicate size must be solved.
- After solving the size, the replicate is unrolled -- which, potentially,
  involves expansion of nested replicate statements.

- After all replicates in the current scope (not hidden by compound actions),
  evaluation of the expanded statements continues.

replicate (2) : L[] {
    a: do A;
    replicate (2) L[] {
      b: do B;
    }
}

Must result in:
L[0].a;
L[0].L[0].b;
L[0].L[1].b;
L[1].a;
L[1].L[0].b;
L[1].L[1].b;

Note: perhaps a good ideal to have an anonymous label array? 

Must implement replicate inside-out. 