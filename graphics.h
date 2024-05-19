#pragma once

// Base
typedef struct RenderPrimitive RenderPrimitive;
void renderPrimitive_render(RenderPrimitive* primitive, HDC hdc);

// Ellipse
typedef struct EllipsePrimitive EllipsePrimitive;
EllipsePrimitive* ellipse_ctor(int x, int y, int w, int h);

// List
typedef struct RenderPrimitiveList RenderPrimitiveList;
void renderPrimitiveList_append(RenderPrimitiveList* list, RenderPrimitive* primitive);
RenderPrimitiveList* renderPrimitiveList_ctor();

// Geters
int renderPrimitiveList_getSize(RenderPrimitiveList* list);
RenderPrimitive* renderPrimitiveList_getElement(RenderPrimitiveList* list, int c);