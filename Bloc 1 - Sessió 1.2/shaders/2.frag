#version 330 core

out vec4 FragColor;

void main() {
    //FragColor = vec4(0, 0, 0, 1);
    if (gl_FragCoord.y < 59. || (gl_FragCoord.y > 117. && gl_FragCoord.y < 177) || (gl_FragCoord.y > 235. && gl_FragCoord.y < 295) || (gl_FragCoord.y > 353. && gl_FragCoord.y < 413) || (gl_FragCoord.y > 471. && gl_FragCoord.y < 531) || (gl_FragCoord.y > 589. && gl_FragCoord.y < 649)) discard;
    
    if (gl_FragCoord.x < 354. && gl_FragCoord.y > 354.) FragColor = vec4(1,0,0,1);
    else if (gl_FragCoord.x < 354. && gl_FragCoord.y < 354.) FragColor = vec4(1,1,0,1);
    else if (gl_FragCoord.x > 354. && gl_FragCoord.y > 354.) FragColor = vec4(0,0,1,1);
    else FragColor = vec4(0,1,0,1);
}

