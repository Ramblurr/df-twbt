static void screen_to_texid_map(renderer_cool *r, int tile, struct texture_fullid &ret)
{
    const unsigned char *s = gscreen + tile*4;

    int bold = (s[3] & 0x0f) * 8;
    int fg   = (s[1] + bold) % 16;
    int bg   = s[2] % 16;

    const long texpos = gscreentexpos[tile];

    if (!texpos)
    {
        ret.tt = 0;
        ret.texpos = map_texpos[s[0]];

        ret.r = enabler->ccolor[fg][0];
        ret.g = enabler->ccolor[fg][1];
        ret.b = enabler->ccolor[fg][2];
        ret.br = enabler->ccolor[bg][0];
        ret.bg = enabler->ccolor[bg][1];
        ret.bb = enabler->ccolor[bg][2];

        return;
    }        

    ret.tt = 1;
    ret.texpos = texpos;

    if (gscreentexpos_grayscale[tile])
    {
        const unsigned char cf = gscreentexpos_cf[tile];
        const unsigned char cbr = gscreentexpos_cbr[tile];

        ret.r = enabler->ccolor[cf][0];
        ret.g = enabler->ccolor[cf][1];
        ret.b = enabler->ccolor[cf][2];
        ret.br = enabler->ccolor[cbr][0];
        ret.bg = enabler->ccolor[cbr][1];
        ret.bb = enabler->ccolor[cbr][2];
    }
    else if (gscreentexpos_addcolor[tile])
    {
        ret.r = enabler->ccolor[fg][0];
        ret.g = enabler->ccolor[fg][1];
        ret.b = enabler->ccolor[fg][2];
        ret.br = enabler->ccolor[bg][0];
        ret.bg = enabler->ccolor[bg][1];
        ret.bb = enabler->ccolor[bg][2];
    }
    else
    {
        ret.r = ret.g = ret.b = 1;
        ret.br = ret.bg = ret.bb = 0;
    }
}

static void screen_to_texid_map_c(renderer_cool *r, int tile, struct texture_fullid &ret)
{
    const unsigned char *s = gscreen + tile*4;

    int bold = (s[3] & 0x0f) * 8;
    int fg   = (s[1] + bold) % 16;
    int bg   = s[2] % 16;

    const long texpos = gscreentexpos[tile];

    if (!texpos)
    {
        ret.tt = 0;
        ret.texpos = map_texpos[s[0]];

        ret.r = enabler->ccolor[fg][0];
        ret.g = enabler->ccolor[fg][1];
        ret.b = enabler->ccolor[fg][2];
        ret.br = enabler->ccolor[bg][0];
        ret.bg = enabler->ccolor[bg][1];
        ret.bb = enabler->ccolor[bg][2];

        return;
    }        

    ret.tt = 1;
    ret.texpos = texpos;

    if (gscreentexpos_grayscale[tile])
    {
        const unsigned char cf = gscreentexpos_cf[tile];
        const unsigned char cbr = gscreentexpos_cbr[tile];

        ret.r = enabler->ccolor[cf][0];
        ret.g = enabler->ccolor[cf][1];
        ret.b = enabler->ccolor[cf][2];
        ret.br = enabler->ccolor[cbr][0];
        ret.bg = enabler->ccolor[cbr][1];
        ret.bb = enabler->ccolor[cbr][2];
    }
    else if (gscreentexpos_addcolor[tile])
    {
        ret.r = enabler->ccolor[fg][0];
        ret.g = enabler->ccolor[fg][1];
        ret.b = enabler->ccolor[fg][2];
        ret.br = enabler->ccolor[bg][0];
        ret.bg = enabler->ccolor[bg][1];
        ret.bb = enabler->ccolor[bg][2];
    }
    else
    {
        ret.r = ret.g = ret.b = 1;
        ret.br = ret.bg = ret.bb = 0;
    }
}

static void screen_to_texid_map_b(renderer_cool *r, int tile, struct texture_fullid &ret)
{
    const unsigned char *s = bscreen + tile*4;

    int bold = (s[3] & 0x0f) * 8;
    int fg   = (s[1] + bold) % 16;
    int bg   = s[2] % 16;

    const long texpos = gscreentexpos[tile];

    if (!texpos)
    {
        ret.tt = 0;
        ret.texpos = map_texpos[s[0]];

        ret.r = enabler->ccolor[fg][0];
        ret.g = enabler->ccolor[fg][1];
        ret.b = enabler->ccolor[fg][2];
        ret.br = enabler->ccolor[bg][0];
        ret.bg = enabler->ccolor[bg][1];
        ret.bb = enabler->ccolor[bg][2];

        return;
    }        

    ret.texpos = texpos;
    ret.tt = 1;

    if (gscreentexpos_grayscale[tile])
    {
        const unsigned char cf = gscreentexpos_cf[tile];
        const unsigned char cbr = gscreentexpos_cbr[tile];

        ret.r = enabler->ccolor[cf][0];
        ret.g = enabler->ccolor[cf][1];
        ret.b = enabler->ccolor[cf][2];
        ret.br = enabler->ccolor[cbr][0];
        ret.bg = enabler->ccolor[cbr][1];
        ret.bb = enabler->ccolor[cbr][2];
    }
    else if (gscreentexpos_addcolor[tile])
    {
        ret.r = enabler->ccolor[fg][0];
        ret.g = enabler->ccolor[fg][1];
        ret.b = enabler->ccolor[fg][2];
        ret.br = enabler->ccolor[bg][0];
        ret.bg = enabler->ccolor[bg][1];
        ret.bb = enabler->ccolor[bg][2];
    }
    else
    {
        ret.r = ret.g = ret.b = 1;
        ret.br = ret.bg = ret.bb = 0;
    }
}

static void write_tile_arrays_map(renderer_cool *r, int x, int y, GLfloat *fg, GLfloat *bg, GLfloat *tex)
{
    struct texture_fullid ret;
    const int tile = x * r->gdimy + y;        
    screen_to_texid_map(r, tile, ret);

    struct texture_fullid retb;
    screen_to_texid_map_b(r, tile, retb);

    struct texture_fullid retc;
    screen_to_texid_map_c(r, tile, retc);


    const unsigned char *sb = bscreen + tile*4;

    GLfloat *_fg  = r->gfgb + tile * 4 * 6;
    GLfloat *_bg  = r->gbgb + tile * 4 * 6;
    GLfloat *_tex = r->gtexb + tile * 2 * 6;
retc.tt = 0;

    if (*sb)
    {
        for (int i = 0; i < 6; i++) {
            *(_fg++) = ret.r;
            *(_fg++) = ret.g;
            *(_fg++) = ret.b;
            *(_fg++) = 1;

            *(fg++) = retb.r;
            *(fg++) = retb.g;
            *(fg++) = retb.b;
            *(fg++) = 1;
            
            *(bg++) = retb.br;
            *(bg++) = retb.bg;
            *(bg++) = retb.bb;
            *(bg++) = 1;
        }
    }
    else
    {
        memset(_fg, 0, sizeof(GLfloat)*6*4);
        memset(_bg, 0, sizeof(GLfloat)*6*4);        
        for (int i = 0; i < 6; i++) {
            *(fg++) = ret.r;
            *(fg++) = ret.g;
            *(fg++) = ret.b;
            *(fg++) = 1;
            
            *(bg++) = ret.br;
            *(bg++) = ret.bg;
            *(bg++) = ret.bb;
            *(bg++) = 1;
        }        
    }
    
    if (has_overrides)
    {
        const unsigned char *s = gscreen + tile*4;
        int s0 = s[0];
//if (s0 == 22)
  //  *out2 << (long*)s<<  " " << (long*) &world->buildings.other[buildings_other_id::IN_PLAY] << (long*) &world->items.other[items_other_id::IN_PLAY] << std::endl;


        //if (s0 == 22)
        if (0)
        {
            int xx = gwindow_x + x;
            int yy = gwindow_y + y;
            int zz = gwindow_z - ((s[3]&0xf0)>>4);
            df::map_block *block = world->map.block_index[xx>>4][yy>>4][zz];
            if (block)
            {
                if (block->designation[xx&15][yy&15].bits.pile)
                {
                    const int tile = x * r->gdimy + y;
                    GLfloat *_fg  = r->gfgb + tile * 4 * 6;
                    GLfloat *_bg  = r->gbgb + tile * 4 * 6;
                    GLfloat *_tex = r->gtexb + tile * 2 * 6;

                    for (int i = 0; i < 6; i++) {
                        *(_fg++) = enabler->ccolor[8][0];
                        *(_fg++) = enabler->ccolor[8][1];
                        *(_fg++) = enabler->ccolor[8][2];
                        *(_fg++) = 1;
                        
                        *(_bg++) = 0;
                        *(_bg++) = 0;
                        *(_bg++) = 0;
                        *(_bg++) = 1;
                    }

                    long texpos = map_texpos[61];

                    gl_texpos *txt = (gl_texpos*) enabler->textures.gl_texpos;
                    *(_tex++) = txt[texpos].left;   // Upper left
                    *(_tex++) = txt[texpos].bottom;
                    *(_tex++) = txt[texpos].right;  // Upper right
                    *(_tex++) = txt[texpos].bottom;
                    *(_tex++) = txt[texpos].left;   // Lower left
                    *(_tex++) = txt[texpos].top;
                    
                    *(_tex++) = txt[texpos].left;   // Lower left
                    *(_tex++) = txt[texpos].top;
                    *(_tex++) = txt[texpos].right;  // Upper right
                    *(_tex++) = txt[texpos].bottom;
                    *(_tex++) = txt[texpos].right;  // Lower right
                    *(_tex++) = txt[texpos].top;


                }
                else if (block->tiletype[xx&15][yy&15] == df::tiletype::StoneFloorSmooth)
                {
                    const int tile = x * r->gdimy + y;
                    GLfloat *_fg  = r->gfgb + tile * 4 * 6;
                    GLfloat *_bg  = r->gbgb + tile * 4 * 6;
                    GLfloat *_tex = r->gtexb + tile * 2 * 6;

                    for (int i = 0; i < 6; i++) {
                        *(_fg++) = enabler->ccolor[7][0];
                        *(_fg++) = enabler->ccolor[7][1];
                        *(_fg++) = enabler->ccolor[7][2];
                        *(_fg++) = 1;
                        
                        *(_bg++) = 0;
                        *(_bg++) = 0;
                        *(_bg++) = 0;
                        *(_bg++) = 1;
                    }

                    long texpos = map_texpos[43];

                    gl_texpos *txt = (gl_texpos*) enabler->textures.gl_texpos;
                    *(_tex++) = txt[texpos].left;   // Upper left
                    *(_tex++) = txt[texpos].bottom;
                    *(_tex++) = txt[texpos].right;  // Upper right
                    *(_tex++) = txt[texpos].bottom;
                    *(_tex++) = txt[texpos].left;   // Lower left
                    *(_tex++) = txt[texpos].top;
                    
                    *(_tex++) = txt[texpos].left;   // Lower left
                    *(_tex++) = txt[texpos].top;
                    *(_tex++) = txt[texpos].right;  // Upper right
                    *(_tex++) = txt[texpos].bottom;
                    *(_tex++) = txt[texpos].right;  // Lower right
                    *(_tex++) = txt[texpos].top;
                }
                else
                {
                    const int tile = x * r->gdimy + y;
                    GLfloat *_fg  = r->gfgb + tile * 4 * 6;
                    GLfloat *_bg  = r->gbgb + tile * 4 * 6;
                    memset(_fg, 0, sizeof(GLfloat)*6*4);
                    memset(_bg, 0, sizeof(GLfloat)*6*4);
                }
            }
        }


        if (overrides[s0])
        {
            int xx = gwindow_x + x;
            int yy = gwindow_y + y;

            if (xx < world->map.x_count && yy < world->map.y_count)
            {

                if (s0 == 88 && df::global::cursor->x == xx && df::global::cursor->y == yy)
                {
                    long texpos = enabler->fullscreen ? cursor_large_texpos : cursor_small_texpos;
                    if (texpos)
                        ret.texpos = texpos;
                }
                else
                {
                    int zz = gwindow_z - ((s[3]&0xf0)>>4);

                    tile_overrides *to = overrides[s0];

                    // Items
                    for (auto it = to->item_overrides.begin(); it != to->item_overrides.end(); it++)
                    {
                        override_group &og = *it;

                        auto ilist = world->items.other[og.other_id];
                        for (auto it2 = ilist.begin(); it2 != ilist.end(); it2++)
                        {
                            df::item *item = *it2;
                            if (!(zz == item->pos.z && xx == item->pos.x && yy == item->pos.y))
                                continue;
                            if (item->flags.whole & bad_item_flags.whole)
                                continue;

                            for (auto it3 = og.overrides.begin(); it3 != og.overrides.end(); it3++)
                            {
                                override &o = *it3;

                                if (o.type != -1 && item->getType() != o.type)
                                    continue;
                                if (o.subtype != -1 && item->getSubtype() != o.subtype)
                                    continue;

                                ret.texpos = enabler->fullscreen ? o.large_texpos : o.small_texpos;
                                goto matched;
                            }
                        }
                    }

                    // Buildings
                    for (auto it = to->building_overrides.begin(); it != to->building_overrides.end(); it++)
                    {
                        override_group &og = *it;

                        auto ilist = world->buildings.other[og.other_id];
                        for (auto it2 = ilist.begin(); it2 != ilist.end(); it2++)
                        {
                            df::building *bld = *it2;
                            if (zz != bld->z || xx < bld->x1 || xx > bld->x2 || yy < bld->y1 || yy > bld->y2)
                                continue;

                            for (auto it3 = og.overrides.begin(); it3 != og.overrides.end(); it3++)
                            {
                                override &o = *it3;

                                if (o.type != -1 && bld->getType() != o.type)
                                    continue;
                                
                                if (o.subtype != -1)
                                {
                                    int subtype = (og.other_id == buildings_other_id::WORKSHOP_CUSTOM || og.other_id == buildings_other_id::FURNACE_CUSTOM) ?
                                        bld->getCustomType() : bld->getSubtype();

                                    if (subtype != o.subtype)
                                        continue;
                                }

                                ret.texpos = enabler->fullscreen ? o.large_texpos : o.small_texpos;
                                goto matched;
                            }
                        }
                    }

                    // Tile types
                    df::map_block *block = world->map.block_index[xx>>4][yy>>4][zz];
                    if (block)
                    {
                        int tiletype = block->tiletype[xx&15][yy&15];

                        for (auto it3 = to->tiletype_overrides.begin(); it3 != to->tiletype_overrides.end(); it3++)
                        {
                            override &o = *it3;

                            if (tiletype == o.type)
                            {
                                ret.texpos = enabler->fullscreen ? o.large_texpos : o.small_texpos;
                                goto matched;
                            }
                        }
                    }
                }
            }
        }
    }
    matched:;


    if (*sb)
    {
        gl_texpos *txt = (gl_texpos*) enabler->textures.gl_texpos;
        {
        *(_tex++) = txt[ret.texpos].left;   // Upper left
        *(_tex++) = txt[ret.texpos].bottom;
        *(_tex++) = txt[ret.texpos].right;  // Upper right
        *(_tex++) = txt[ret.texpos].bottom;
        *(_tex++) = txt[ret.texpos].left;   // Lower left
        *(_tex++) = txt[ret.texpos].top;
        
        *(_tex++) = txt[ret.texpos].left;   // Lower left
        *(_tex++) = txt[ret.texpos].top;
        *(_tex++) = txt[ret.texpos].right;  // Upper right
        *(_tex++) = txt[ret.texpos].bottom;
        *(_tex++) = txt[ret.texpos].right;  // Lower right
        *(_tex++) = txt[ret.texpos].top;

        *(tex++) = txt[retb.texpos].left;   // Upper left
        *(tex++) = txt[retb.texpos].bottom;
        *(tex++) = txt[retb.texpos].right;  // Upper right
        *(tex++) = txt[retb.texpos].bottom;
        *(tex++) = txt[retb.texpos].left;   // Lower left
        *(tex++) = txt[retb.texpos].top;
        
        *(tex++) = txt[retb.texpos].left;   // Lower left
        *(tex++) = txt[retb.texpos].top;
        *(tex++) = txt[retb.texpos].right;  // Upper right
        *(tex++) = txt[retb.texpos].bottom;
        *(tex++) = txt[retb.texpos].right;  // Lower right
        *(tex++) = txt[retb.texpos].top;        
    }

{
        *(tex++) = txt[ret.texpos].left;   // Upper left
        *(tex++) = txt[ret.texpos].bottom;
        *(tex++) = txt[ret.texpos].right;  // Upper right
        *(tex++) = txt[ret.texpos].bottom;
        *(tex++) = txt[ret.texpos].left;   // Lower left
        *(tex++) = txt[ret.texpos].top;
        
        *(tex++) = txt[ret.texpos].left;   // Lower left
        *(tex++) = txt[ret.texpos].top;
        *(tex++) = txt[ret.texpos].right;  // Upper right
        *(tex++) = txt[ret.texpos].bottom;
        *(tex++) = txt[ret.texpos].right;  // Lower right
        *(tex++) = txt[ret.texpos].top;    
    }
    }
    else
    {

    // Set texture coordinates
    gl_texpos *txt = (gl_texpos*) enabler->textures.gl_texpos;
    *(tex++) = txt[ret.texpos].left;   // Upper left
    *(tex++) = txt[ret.texpos].bottom;
    *(tex++) = txt[ret.texpos].right;  // Upper right
    *(tex++) = txt[ret.texpos].bottom;
    *(tex++) = txt[ret.texpos].left;   // Lower left
    *(tex++) = txt[ret.texpos].top;
    
    *(tex++) = txt[ret.texpos].left;   // Lower left
    *(tex++) = txt[ret.texpos].top;
    *(tex++) = txt[ret.texpos].right;  // Upper right
    *(tex++) = txt[ret.texpos].bottom;
    *(tex++) = txt[ret.texpos].right;  // Lower right
    *(tex++) = txt[ret.texpos].top;
}
}