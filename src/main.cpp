#include "NuakeRenderer/NuakeRenderer.h"
#include "NuakeRenderer/Window.h"
#include "NuakeRenderer/VertexBuffer.h"
#include "NuakeRenderer/VertexArray.h"
#include "NuakeRenderer/VertexBufferLayout.h"
#include "NuakeRenderer/ShaderRegistry.h"
#include "NuakeRenderer/Texture.h"
#include "NuakeRenderer/FrameBuffer.h"

#include <vector>

void main()
{
	// Create a window and enable debugging.
	auto primaryWindow   = new NuakeRenderer::Window("Primary Window", {600, 600});
	// We can apply the nuake imgui theme(optional)
	NuakeRenderer::ApplyNuakeImGuiTheme();
	
	//// Let's create a framebuffer and attach a texture to it.
	//Vector2 framebufferSize = Vector2(1280, 720);
	//auto texture = new NuakeRenderer::Texture({}, framebufferSize);
	//auto framebuffer = new NuakeRenderer::Framebuffer(framebufferSize);
	//
	//// Here we chose the texture attachment and attach the texture.
	//framebuffer->SetTextureAttachment(texture, NuakeRenderer::TextureAttachment::COLOR0);
    
	// Let's create a quad with an index buffer.
	auto vertices = std::vector<Vector3>({
		{.5f, .5f, 0.f },
		{.5f, -.5f, 0.f},
		{-.5f, -0.5f, 0.f},
		{-.5f, .5f, 0.f}
    });
    
	// The indices.
	const std::vector<unsigned int> mIndices = {
		0, 1, 3, 1, 2, 3
	};
    
	// Let's create the necessay buffers
	auto vertexArray = new NuakeRenderer::VertexArray();
	vertexArray->Bind();
    
	auto vertexBuffer = new NuakeRenderer::VertexBuffer(vertices.data(), (unsigned int)(vertices.size() * sizeof(Vector3)));
	auto elementBuffer = new NuakeRenderer::VertexBuffer(mIndices.data(), (unsigned int)(mIndices.size() * sizeof(unsigned int)), GL_ELEMENT_ARRAY_BUFFER);
	
	// We only have 3 floats for the positon. we dfine the layout of a vertex here.
	auto layout = NuakeRenderer::VertexBufferLayout();
	layout.Push<float>(3);
    
	vertexArray->AddBuffer(*vertexBuffer, layout);
	vertexArray->Unbind();
    
	// Now let's create a basic shader that takes in the position and a color.
	std::string vertexSource = 
        "#version 460 core \n"
        "layout(location = 0) in vec3 Position; "
        "void main() { "
		"gl_Position = vec4(Position, 1.0f); "
        "}";
    
	std::string fragmentSource = 
        "#version 460 core \n"
        "out vec4 FragColor; "
        "uniform vec4 uColor; "
        "void main() { "
		"FragColor = uColor; "
        "}";
    
	// Lets create a shader and register it to the registry so we can find it by name.
	// using the registry is completly optional you are free to handle the shaders yourself.
	auto shader = new NuakeRenderer::Shader(vertexSource, fragmentSource);
	NuakeRenderer::ShaderRegistry::Set("default_shader", shader);
    
	// Let's render!
	while (!primaryWindow->ShouldClose())
	{
		// Here we poll for the window events.
		NuakeRenderer::PollEvents();
        
		// Clear the window.
		NuakeRenderer::SetClearColor(.1f, .1f, .1f, 1.f);
		NuakeRenderer::Clear();
        
		// Let's render to the framebuffer we created earlier.
		//framebuffer->Bind();
		//{
		// Here is how you can retrieve a shader from the registry using the name we 
		// used earlier.
		auto shader = NuakeRenderer::ShaderRegistry::Get("default_shader");
		shader->Bind();
        
		// Here we are using the SetUniforms so we can set multiple uniforms at once.
		// but we only have one.
		shader->SetUniforms({
			{ "uColor", Vector4(0, 1, 0, 1) }
        });
        
		// Let's bind the vertex array and draw it.
		vertexArray->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		//}
		//framebuffer->Unbind();
        
		// Now let's draw some ImGui stuff.
		NuakeRenderer::BeginImGuiFrame();
		{
			if (ImGui::Begin("Viewport"))
			{
				//ImGui::Image((void*)framebuffer->GetTextureAttachment(NuakeRenderer::TextureAttachment::COLOR0)->GetTextureID(), ImGui::GetContentRegionAvail());
			}
			ImGui::End();
		}
		NuakeRenderer::EndImGuiFrame();
        
		// We swap the buffer to display our new frame in the window.
		primaryWindow->SwapBuffers();
	}
}