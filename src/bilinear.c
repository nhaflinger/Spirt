float textureLookup(Texture tex, int interp, float s, float t, int channel) {
    float x,y;
    float xsize, ysize;
    float value = 0;

    xsize = tex->getXsize();
    ysize = tex->getYsize();

    if(interp == BILINEAR) {	// bilinear interpolation
        float a,b,c,d,ab,cd;
        int x0,y0;
        int x1,y1;
        float dx,dy;
    
        x = s*xsize;
        y = t*ysize;
        if(x >= 0.0) x0 = (int)x;
        else x0 = (int)(x - 1.0);
        if(y >= 0.0) y0 = (int)y;
        else y0 = (int)(y - 1.0);
        x1 = x0 + 1;
        y1 = y0 + 1;
      
        dx = x - x0;
        dy = y - y0;
    
        a = b = c = d = ab = cd = 0;
      
        if(x0>=0 && x0<xsize && y0>=0 && y0<ysize) a = tex->getPixel(x0, y0, channel);
        if(x1>=0 && x1<xsize && y0>=0 && y0<ysize) b = tex->getPixel(x1, y0, channel);
        if(x0>=0 && x0<xsize && y1>=0 && y1<ysize) c = tex->getPixel(x0, y1, channel);
        if(x1>=0 && x1<xsize && y1>=0 && y1<ysize) d = tex->getPixel(x1, y1, channel);
    
        ab = a * (1 - dx) + b * dx;
        cd = c * (1 - dx) + d * dx;
    
        value = ab*(1-dy) + cd*dy;
    }
    else {	// nearest neighbor
        x = s*(xsize + 0.5);
        y = t*(ysize + 0.5);
        value = getPixelValue(x, y, channel);
    }

    return value;
}

