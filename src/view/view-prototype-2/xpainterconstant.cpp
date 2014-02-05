#include "xpainterconstant.h"
#include <QPen>
#include <QBrush>

const XPainterConstant XPainterConstant::_singleton;

XPainterConstant::XPainterConstant() :
    _color(new const QColor* [NUM_COLORS]),
    _pen(new const QPen* [NUM_PENS]),
    _brush(new const QBrush* [NUM_BRUSHES])
{
    initColor();
    initPen();
    initBrush();
}

XPainterConstant::~XPainterConstant()
{
    for (int i = 0; i < NUM_BRUSHES; ++i)
        delete _brush;
    delete[] _brush;
    _brush = 0;

    for (int i = 0; i < NUM_PENS; ++i)
        delete _pen;
    delete[] _pen;
    _pen = 0;

    for (int i = 0; i < NUM_COLORS; ++i)
        delete _color;
    delete[] _color;
    _color = 0;
}

void XPainterConstant::initColor()
{
    _color[COLOR_DEFAULT_FILL] = new QColor(137, 122, 186);
    _color[COLOR_DEFAULT_BOUNDARY] = new QColor(99, 88, 136);
}

void XPainterConstant::initPen()
{
    _pen[PEN_DEFAULT_BOUNDARY] = new QPen(getColor(COLOR_DEFAULT_BOUNDARY), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
}

void XPainterConstant::initBrush()
{
    _brush[BRUSH_DEFAULT_FILL] = new QBrush(getColor(COLOR_DEFAULT_FILL));
}
