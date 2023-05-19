# week 13
## convex hull

### algorithm 
1. Find a point we know to line on the convex hull for sure (choose the bottom right)
https://miro.medium.com/v2/resize:fit:552/format:webp/1*Ffi0OP13KKmSgrGlA6M2lw.png
2. sort the other points by the angle at which they lie ** as seen from the starting point ** .
> If two points happen to be at the same angle, the point that is closer to the starting point should occur earlier in the sorting
https://miro.medium.com/v2/resize:fit:542/format:webp/1*NDrQAtknuoEa1O2i0NFJWw.png
3. walk around this sorted array, determining for every point, whether or not it lies on the convex hull. If the corner is concave, the middle point out of this triplet can't lie on the convex hull

4. store the points that lie on the convex hull on the convex hull on a stack.

5. Going around the sorted array of points, we add the point to the stack, and if we later on find that the point doesn't belong to the convex hull, we remove it

 > we measure whether the current corner bends inwards or outwards by calculating the cross product and checking if that is positive or negative