double cir_area_inst(Point c1, double r1, Point c2, double r2) {            // 两圆面积交
    double a1, a2, d, ret;
    d = sqrt((c1.x-c2.x)*(c1.x-c2.x)+(c1.y-c2.y)*(c1.y-c2.y));
    if ( d > r1 + r2 - eps )
        return 0;
    if ( d < r2 - r1 + eps )
        return pi*r1*r1;
    if ( d < r1 - r2 + eps )
        return pi*r2*r2;
    a1 = acos((r1*r1+d*d-r2*r2)/2/r1/d);
    a2 = acos((r2*r2+d*d-r1*r1)/2/r2/d);
    ret = (a1-0.5*sin(2*a1))*r1*r1 + (a2-0.5*sin(2*a2))*r2*r2;
    return ret;
}