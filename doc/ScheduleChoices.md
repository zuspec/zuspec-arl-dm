
All scheduling choices must be expressed as set-wise selection.

- Structural Selection
  - Skip: if no conditional sections
  - Choose target branches in
    - if/then/else
    - select
    - match
    - generate
  - Output: 
    - Actions and binds to be scheduled
    - Scheduling arcs to final actions covering both
      selected statemets and selected schedule constraints
  - Assumptions: 
    - Constraints matching to selected condition
      - eg <match_cond> == <selected_branch>

- Explicit Action Component Assignment
  - Choose component assignment of explicitly-traversed actions
    - Each component is given an id
    - Each action type has a set of legal component assignments
    - Each action type has 
  - Output:
    - Single assignment for each action
  - Cutoff Opportunities
    - Constraints on context value (value < 2)
    - Constraints on component (comp != this.comp.foo)
    
- Implied Binds
  - Skip: if no unbound references with candidate producers
    - Set of actions with input requirements
    - For each, a set of actions that produce outputs
    - 
  - Evaluate candidate 
  - In 
  - Assumptions:
    - New scheduling assumptions
  - Cutoff Opportunities
    - Schedule violates requirements
    - Connections violate constraint requirements

- Inference 
  - Skip: if no unbound references
  - Choose actions to complete partial specification
    - Have component assignment, so know which pools we're dealing with
    - Know inference max, so can build chains to match
  - Output:
    - New actions to satisfy unbound references
  - Assumptions:
    - Binding of each action (it's basically 1:1, since we select one solution)
    - Scheduling dependency arcs
  - Cutoff Opportunities
    - Isolated solve. For example, if X,Y,Z cannot result in proper state, then no point in proceeding    

- Inferred Action Component Assignment
  - Skip: if no inferred actions
  - Choose component assignment of candidate inferred actions
    - Know the pool context
    - Search down to find candidate contexts
  - Output:
    - Single assignment for each action
  - Cutoff Opportunities
    - Constraints on context value (value < 2)
    - Constraints on component (comp != this.comp.foo)
    
- 

Question: think of this as steps encompasing all actions, or as steps
applied to each action?

Question: how do we bound the problem to keep modular?

Question: how much can we do with very little of this full algorithm?
  - No inference
  - Explicit scheduling
  - Explicit singleton binding
  - No activity branches


