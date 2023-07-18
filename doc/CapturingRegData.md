
- TypeField has captures field offset using initial-value expression
- ModelField for root reg-model block stores addr_handle_t as value 
- Define addr_handle_t as:
  - [64] offset
  - [32] aspace_id
  - [32] region_id


- Could give each field an offset
- Could give each DataTypeStruct a size in bytes