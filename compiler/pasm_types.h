#if !defined ( PASM_TYPES_H )
#define PASM_TYPES_H

#if defined ( __cplusplus )
extern "C" {
#endif

#define MAX_FIXUP_TRIES 5
#define INVALID_INSTR 0xFF
#define SYMBOL_NOT_FOUND 0xFFFFFFFF

typedef struct _macro_table
{
   int idx; // used for self-reference and also for scoping variables
   char* symbol;
   struct _ir_table* ir_head;
   struct _ir_table* ir_tail;
} macro_table;

typedef struct _text_type
{
   char* string;
   int   length;
} text_type;

typedef enum
{
   symbol_global,
   symbol_label
} symbol_type;

typedef struct _symbol_table
{
   int            idx;
   char*          symbol;
   struct _ir_table* ir;
   struct _expr_type* expr;
   unsigned int  btab_ent;
   int           scope;
} symbol_table;

typedef union _ref_union
{
   char* symbol;
   int stab_ent;
   struct _ir_table* stake;
   struct _text_type* text;
} ref_union;

typedef enum
{
   reference_symbol,
   reference_symtab,
   reference_stake,
   reference_const_string
} reference_type;

typedef struct _ref_type
{
   reference_type type;
   union _ref_union ref;
} ref_type;

typedef struct _number_type
{
   int number;
   unsigned char zp_ok;
} number_type;

typedef enum
{
   expression_operator,
   expression_number,
   expression_reference
} expression_type;

typedef enum
{
   value_is_int,
   value_is_string
} value_type;

typedef struct _expr_type
{
   expression_type type;
   union
   {
      number_type* num;
      ref_type*    ref;
      char         op;
   } node;
   struct _expr_type* left;
   struct _expr_type* right;
   struct _expr_type* parent;
   value_type vtype;
   union
   {
      int ival;
      text_type* sval;
   } value;
} expr_type;

typedef enum
{
   fixup_fixed,
   fixup_immediate,
   fixup_absolute,
   fixup_zeropage,
   fixup_abs_idx_x,
   fixup_abs_idx_y,
   fixup_zp_idx,
   fixup_indirect,
   fixup_pre_idx_ind,
   fixup_post_idx_ind,
   fixup_relative,
   fixup_datab,
   fixup_dataw,
   fixup_align
} fixup_type;

typedef struct _ir_table
{
   unsigned char data[3];
   unsigned int  btab_ent;
   unsigned int  addr;
   unsigned int  len;
   unsigned char emitted;
   unsigned char multi;
   unsigned char align;
   unsigned char fixed;
   unsigned char label;
   fixup_type    fixup;
   int           source_linenum;
   struct _ir_table* next;
   struct _ir_table* prev;
   struct _expr_type* expr;
} ir_table;

#define ANONYMOUS_BANK "_anonymous_"

typedef int (*incobj_callback_fn) ( char* objname, char** objdata, int* size );

typedef enum _segment_type
{
   text_segment,
   data_segment
} segment_type;

typedef struct _binary_table
{
   int            idx;
   segment_type   type;
   char*          symbol;
   unsigned int   addr;
} binary_table;

#if defined ( __cplusplus )
}
#endif

#endif
