#version 440

layout(location = 0) in vec2 qt_TexCoord0;
layout(location = 0) out vec4 fragColor;

layout(binding = 1) uniform sampler2D image;
layout(binding = 2) uniform sampler2D mask;

void main() {
    fragColor = texture(image, qt_TexCoord0) *
                texture(mask, qt_TexCoord0).a;
}
