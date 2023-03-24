attribute vec4 a_position;
attribute vec2 a_tex_coord0;
varying vec2 v_tex_coord0;

uniform float uf_time;
uniform mat4 um4_matrix;
uniform mat4 um4_pmatrix;
const float cf_divisor = 16.0;

void main(void) {
    vec4 pos = a_position;
    float fX = abs(pos.x);
    float fY = abs(pos.y);

    // Move X and Y coordinates
    // in toward the center.
    // Apply to corner vertices
    // only.
    if (fX == 1.0 && fY == 1.0)
    {
        float f_offset = 1.0 - (uf_time/cf_divisor);
        pos.x *= f_offset;
        pos.y *= f_offset;
    }
    // Move center vertices
    // toward the viewport.
    else if (fX == 0.0 && fY == 0.0)
    {
        pos.z = uf_time;
    }
    gl_Position = um4_pmatrix * um4_matrix * pos;
    v_tex_coord0 =  a_tex_coord0;
}