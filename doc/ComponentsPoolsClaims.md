
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

