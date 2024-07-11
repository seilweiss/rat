#ifndef XHUDTEXT_H
#define XHUDTEXT_H

#include "xHud.h"
#include "xFont.h"

namespace xhud {

struct text_asset;

class text_widget : public widget
{
public:
    struct widget_chunk;

    char text[128];
    xtextbox tb;

    static void load(xBase& data, xDynAsset& asset, size_t asset_size);

    text_widget(const text_asset& a);

    void destruct();
    virtual void setup();
    virtual void destroy();
    virtual U32 type() const;
    virtual bool is(U32 id) const;
    virtual void update(F32 dt);
    virtual void render();
    virtual void set_text(const char* intext);

#ifdef DEBUGRELEASE
    virtual const char* category() { return "Text"; }
#endif
};

struct text_widget::widget_chunk : xBase
{
    text_widget w;
};

}

#endif
