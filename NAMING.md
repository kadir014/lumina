# Lumina Game Engine Naming Conventions

- **Trivial variables**: `i` for index, `n` for amount or size of data, etc.. It should be clear enough.
- **Local variables**: `snake_case`
- **Public Functions**: `lm_snake_case`
- **Private functions**: `_lm_snake_case`
- **Const variable**: `SCREAMING_SNAKE_CASE`
- **Structs**: `lmPascalCase`
  - **Members**: `snake_case`
  - **Methods**: `lmPascalCase_snake_case`
  - **Example**:
  ```c
  typedef struct {
      int member_of_struct;
  } lmSomeStruct;

  void *lmSomeStruct_some_method(void);
  ```
- **Enums**: `lmPascalCase`
  - **Fields**: `lmPascalCase_SCREAMING_SNAKE_CASE`
  - **Example**:
  ```c
  typedef enum {
      lmSomeEnum_FIRST;
      lmSomeEnum_SECOND_FIELD;
      lmSomeEnum_LAST;
  } lmSomeEnum;
  ```
- **Macros**: `LM_SCREAMING_SNAKE_CASE`