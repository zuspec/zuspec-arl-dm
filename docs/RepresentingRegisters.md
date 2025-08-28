# Representing Registers

Like many elements in an ARL model, registers have both a type and a model 
aspect. Unlike other situations, the type and model are not symmetrical.
In most other cases, a flattened type hierarchy is elaborated into an 
expanded model hierarchy. In the case of registers, a model element 
exists for the root of each register group, but the rest of the register 
model has only a type representation.

Each register-group and register-group ref has a base address. This
base address will be calculated and stored in the context
- In other words, the target representation of a reg-group or 
  reg-group ref field is an addr_handle_t field


Question: does it make sense to support register blocks inside actions?
- Use model would be when the base address is variable in some way

- Represent register-group as a chandle in output C code
- Represent register-group-ref as a chandle pointer in output C code

- Assignment to register-ref field results in:
  - Specifying originating register block (ie where to get base address)
  - Specifying offset of that register block. This can be computed
    based on the type of the originating register block.


## TODO: how to deal with ref chains
- Assume assignments are in order
- 

All register read/write accesses can be treated as mmio read/write 
accesses relative to the base address held in the component data.
