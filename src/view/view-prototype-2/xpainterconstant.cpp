#include "xpainterconstant.h"
#include <QPen>
#include <QBrush>

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
        delete _brush[i];
    delete[] _brush;
    _brush = 0;

    for (int i = 0; i < NUM_PENS; ++i)
        delete _pen[i];
    delete[] _pen;
    _pen = 0;

    for (int i = 0; i < NUM_COLORS; ++i)
        delete _color[i];
    delete[] _color;
    _color = 0;
}

const XPainterConstant &XPainterConstant::singleton()
{
    static const XPainterConstant singletonObj;
    return singletonObj;
}

void XPainterConstant::initColor()
{
    _color[COLOR_DEFAULT_FILL] = new QColor(137, 122, 186);
    _color[COLOR_DEFAULT_BOUNDARY] = new QColor(99, 88, 136);
    _color[COLOR_SELECT_FILL] = new QColor(137, 122, 186, 127);
    _color[COLOR_SELECT_BOUNDARY] = new QColor(161, 155, 184);
}

void XPainterConstant::initPen()
{
    _pen[PEN_DEFAULT_BOUNDARY] = new QPen(colorPrivate(COLOR_DEFAULT_BOUNDARY), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    _pen[PEN_SELECT_BOUNDARY] = new QPen(colorPrivate(COLOR_SELECT_BOUNDARY), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
}

void XPainterConstant::initBrush()
{
    _brush[BRUSH_DEFAULT_FILL] = new QBrush(colorPrivate(COLOR_DEFAULT_FILL));
    _brush[BRUSH_SELECT_FILL] = new QBrush(colorPrivate(COLOR_SELECT_FILL));
}
