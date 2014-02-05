#ifndef XPAINTERCONSTANT_H
#define XPAINTERCONSTANT_H

class QColor;
class QPen;
class QBrush;

class XPainterConstant
{
private: // private constructor and distructor make the singleton
    XPainterConstant();
    ~XPainterConstant();

public:
    enum ColorEnum { // DO NOT modify any of the following values!
        COLOR_DEFAULT_FILL, COLOR_DEFAULT_BOUNDARY,
        NUM_COLORS // NUM_COLORS must be the last element!
    };
    enum PenEnum { // DO NOT modify any of the following values!
        PEN_DEFAULT_BOUNDARY,
        NUM_PENS // NUM_PENS must be the last element!
    };
    enum BrushEnum { // DO NOT modify any of the following values!
        BRUSH_DEFAULT_FILL,
        NUM_BRUSHES // NUM_BRUSHES must be the last element!
    };

public:
    static const QColor &color(const ColorEnum n) { return _singleton.getColor(n); }
    static const QPen &pen(const PenEnum n) { return _singleton.getPen(n); }
    static const QBrush &brush(const BrushEnum n) {return _singleton.getBrush(n); }

private:
    const QColor **_color;
    const QPen **_pen;
    const QBrush **_brush;

private:
    void initColor();
    void initPen();
    void initBrush();
    const QColor &getColor(const ColorEnum n) const { return *_color[n]; }
    const QPen &getPen(const PenEnum n) const { return *_pen[n]; }
    const QBrush &getBrush(const BrushEnum n) const { return *_brush[n]; }

private:
    static const XPainterConstant _singleton;
};

#endif // XPAINTERCONSTANT_H
