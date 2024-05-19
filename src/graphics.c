#include <windows.h>
#include "graphics.h"

typedef void (*primitiveRendererFunction)(HDC hdc, int x, int y, int w, int h);

void __ellipse_draw(HDC hdc, int x, int y, int w, int h);

typedef struct RenderPrimitive {
    primitiveRendererFunction func;
    int x; 
    int y; 
    int w;
    int h;
} RenderPrimitive;


RenderPrimitive* renderPrimitive_ctor(primitiveRendererFunction func, int x, int y, int w, int h) {
    RenderPrimitive* primitive = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*primitive));
    primitive->func = func;
    primitive->x = x;
    primitive->y = y;
    primitive->w = w;
    primitive->h = h;
    return primitive;
}

void renderPrimitive_render(RenderPrimitive* primitive, HDC hdc) {
    primitive->func(hdc, primitive->x, primitive->y, primitive->w, primitive->h);
}

typedef struct EllipsePrimitive {
    RenderPrimitive primitive;
} EllipsePrimitive;


EllipsePrimitive* ellipse_ctor(int x, int y, int w, int h) {
    RenderPrimitive* primitive = renderPrimitive_ctor(__ellipse_draw, x, y, w, h);
    return (EllipsePrimitive*)primitive;
}

void ellipse_dtor(EllipsePrimitive* ellipse) {

}


void __ellipse_draw(HDC hdc, int x, int y, int w, int h) {
    Ellipse(hdc, x, y, w, h);
}



// List 


typedef struct RenderPrimitiveList {
    RenderPrimitive** arr;
    UINT capacity;
    UINT len;
} RenderPrimitiveList;

RenderPrimitiveList* renderPrimitiveList_ctor() {
    HANDLE h = GetProcessHeap();
    RenderPrimitiveList* list = (RenderPrimitiveList*)HeapAlloc(h, HEAP_ZERO_MEMORY, sizeof(*list));
    list->capacity = 10;
    list->len = 0;
    list->arr = (RenderPrimitive**)HeapAlloc(h, HEAP_ZERO_MEMORY, list->capacity * sizeof(*list->arr));
    return list;
}

void renderPrimitiveList_append(RenderPrimitiveList* list, RenderPrimitive* primitive) {
    list->arr[list->len] = primitive;
    if(++list->len >= list->capacity) {
        list->capacity += 10;
        list->arr = HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, list->arr, list->capacity * sizeof(*list->arr));
    }
}

int renderPrimitiveList_getSize(RenderPrimitiveList* list) {
    return list->len;
}

RenderPrimitive* renderPrimitiveList_getElement(RenderPrimitiveList* list, int c) {
    if(c <= list->len && list->arr[c] != NULL) {
        return list->arr[c];
    }
    return NULL;
}