
# Components, Pools, and Claims

Each action is assigned to a component during execution. Actions have
a 'comp' reference field through which the selected component is 
accessed. 

Each flow object contains a built-in 'pool_id' field that tags the pool
to which it belongs. Producer and consumer must agree on the pool id.

Pool id is derived from action component context. Given a component
context, the pool id for any type is statically known.

Actions select component context by index from a list of components.
Each index maps to a component id.

Each action has a list of candidate component indices and, by extension,
a list of candidate pools for any flow-object type.

foreach comp_sel in valid_action_contexts:
    (comp_selector == comp_sel) -> (flow_object_type_pool_id == YY)

# These constraints are placed on the ref/claim field. The ref unroll
# logic will handle replicating these (?)
foreach action_model in action_models:
  foreach out_ref_claim in action_model.claim_refs():
    foreach comp_sel in valid_action_contexts:
      (comp_selector == comp_sel) -> (claim_ref.pool_id == comp_sel_pool_id)

Output refs are not a selector (?). It is nice to implement output refs as
a reference, but the semantics are different. Output refs are initialized
to their target in the pool. They always point to a single object.

We basically want output refs to be simple redirects to a single known 
object.

(comp_selector == 0) -> ref1->pool_id == 2;
(comp_selector == 1) -> ref1->pool_id == 3;

Input refs and claims are true references. 

(comp_selector == 0) -> (ref2->pool_id == 2;)

(comp_selector == 0) -> (
    ref2_sel in [0,1,2]
    (ref2_sel == 0) -> (obj[0].pool_id == 2;)
    (ref2_sel == 1) -> (obj[1].pool_id == 2;)
    (ref2_sel == 2) -> (obj[2].pool_id == 2;)
)
(comp_selector == 1) -> (
    ref2_sel in [3,4,5]
    (ref2_sel == 3) -> (obj[4].pool_id == 3;)
    (ref2_sel == 4) -> (obj[5].pool_id == 3;)
    (ref2_sel == 5) -> (obj[6].pool_id == 3;)
)

Note: it's possible that it would be better to arrange this
so that each claim selects the target pool, and the target
pools combine to constrain the component context.

ref2_sel in [0,1,2] # <- This constraint is selector specific
ref2.pool_id in [2,4]

(ref2.pool_id == 2) -> comp_selector == 0;
(ref2.pool_id == 4) -> comp_selector == 1;

// Note: this will be expanded as:
(ref2_sel == 0) -> {
  (obj[0].pool_id in [2,4])
  (obj[0].pool_id == 2) -> comp_selector == 0;
  (obj[0].pool_id == 4) -> comp_selector == 1;
}
(ref2_sel == 1) -> {
  (obj[1].pool_id in [2,4])
  (obj[1].pool_id == 2) -> comp_selector == 0;
  (obj[1].pool_id == 4) -> comp_selector == 1;
}
(ref2_sel == 2) -> {
  (obj[2].pool_id in [2,4])
  (obj[2].pool_id == 2) -> comp_selector == 0;
  (obj[2].pool_id == 4) -> comp_selector == 1;
}

Note: I think we can do this without too many conditionals.
For each ref/component context combination, there is a single
pool of interest. Both producer and consumer must publish
and agree on the pool in order to share an object

Producer:
(comp_selector == 0) -> out.pool_id == 1;
(comp_selector == 1) -> out.pool_id == 2;


Consumer:
(comp_selector == 0) -> {
  in_ref_sel in [...]; // This is due to ordering, and not
                       // due to pool
                       // Should be able to limit unrolling to 
                       // this subset
  in.pool_id == 1;     // Pool is directly related to comp_selector
                       // Unrolling converts to per-object constraints
}

(comp_selector == 1) -> {
  in_ref_sel in [...];
  in.pool_id == 2;
}

# Process

- Each action type has a set of possible component contexts within the tree
- The valid possibilities are determined by the parent ID. In other words, the
  component-ref index of the containing action
- Aside from the specific variables referenced, these constraints (the form)
  are the same for every action instance
- Each action inside a compound action requires a set of constraints to relate
  the component context of the container to the valid component contexts 
  for itself

- Each action ref/claim has 0..1 associated pools for each component context
  - Valid component contexts are the intersect of contexts where all
    refs/claims have a valid pool

Think we want to have the ability to build 
activity -> schedule-info -> solve-data

Schedule info collects scheduling choices. It is not, on its own, sufficient
to use for solving. It is used to inform creation of the solve data, such 
that we don't have to co-build schedule-info and solve-data simultaneously.

Schedule Info
- Entry for each component context
  - List
  - Map Ptr -> Idx
- Resource information
  - List of Types
    - 
  - Map Ptr -> Idx
- Flow-object information
  - List of Types
    - Per-type list of objects
  - Map Ptr -> Idx
- Entry for each action traversal
  - List
    - Action-traversal data
      - Index of containing region or -1 (root)
      - List of available component contexts
      - List of outputs
        - 
      - List of inputs
      - List of claims
  - Map Ptr -> Idx
- Entry for each scheduled region
  - List
    - Scheduled region data
      - Handle to root activity
      - List of action indices
      - List of pair variables (0=unconstrained, 1..4=constrained)
      - Map Tuple -> index
  - Map Ptr -> Idx

Scheduled regions must be built in two steps:
- Count actions within the region in order to build schedule map
- Collect actions within the region 

Pairwise creation / unrolling

x,y where x < y

0
1
2
3
4
5

Index is ((N*(N-1))/2 - ((N-f)*(N-f-1))/2 + s

1000 actions is ~500k variables

Notes:
- Resources are managed differently because there is a fixed relationship between
  consumer component context and pool. Unlike with flow objects, we don't need to
  pair producer action pool and consumer action pool.
- Resource information is basically static to the component tree.
- Parent/child context info is also basically static to the component tree.
-  

For objects, we need to do the following:
- 

Each action has the following solve data:
- Component reference selector
- Claim/Ref selector for each claim or object reference

Before building action solve data, must know:
- Component contexts that this action may use
- 

During action-data build, may compute the following:
- Object set of a given type
  - Buffer objects added to buffer collection
  - State added to state collection
  - Stream objects added to stream collection (need to be temporary?)
    - This bears more thought...
- Component-inst/pool-type mapping
  - When an object has a ref of type X, must compute the mapping 
    between comp-ref and pool

Have:
- Global solve data
  - Component map and object list
  - Component -> pool map
  - List of all selectors
  - List of all traversals
  - Map<Type,List<Object>> of all flow objects

- Action solve data -- primarily to use in reacting to failures
  - Handle to component reference selector
  - Handle to claim/ref field selectors
  - 

Ideally, we would incrementally change the solve data during
inferencing instead of rebuilding from scratch

