#define ITEM_ID_LEN 20
#define ARTICULO_LEN 200
#define PRODUCTO_LEN 80
#define MARCA_LEN 80

typedef struct
{
    char item_id[ITEM_ID_LEN];
    char articulo[ARTICULO_LEN];
    char producto[PRODUCTO_LEN];
    char marca[MARCA_LEN];
}t_Articulo;