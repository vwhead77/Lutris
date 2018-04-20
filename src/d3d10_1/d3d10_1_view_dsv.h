#pragma once

#include "../dxvk/dxvk_device.h"

#include "d3d10_1_device_child.h"

namespace dxvk {
  
  class D3D10Device;
  
  /**
   * \brief Depth-stencil view
   * 
   * Unordered access views are special in that they can
   * have counters, which can be used inside shaders to
   * atomically append or consume structures.
   */
  class D3D10DepthStencilView : public D3D10DeviceChild<ID3D10DepthStencilView> {
    
  public:
    
    D3D10DepthStencilView(
            D3D10Device*                      device,
            ID3D10Resource*                   resource,
      const D3D10_DEPTH_STENCIL_VIEW_DESC&    desc,
      const Rc<DxvkImageView>&                view);
    
    ~D3D10DepthStencilView();
    
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) final;
    
    void STDMETHODCALLTYPE GetDevice(ID3D10Device** ppDevice) final;
    
    void STDMETHODCALLTYPE GetResource(ID3D10Resource** ppResource) final;
    
    void STDMETHODCALLTYPE GetDesc(D3D10_DEPTH_STENCIL_VIEW_DESC* pDesc) final;
    
    D3D10_RESOURCE_DIMENSION GetResourceType() const {
      D3D10_RESOURCE_DIMENSION type;
      m_resource->GetType(&type);
      return type;
    }
    
    Rc<DxvkImageView> GetImageView() const {
      return m_view;
    }
    
    VkImageLayout GetRenderLayout() const {
      /*switch (m_desc.Flags & (D3D10_DSV_READ_ONLY_DEPTH | D3D10_DSV_READ_ONLY_STENCIL)) {
        default:  // case 0
          return VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
        case D3D10_DSV_READ_ONLY_DEPTH:
          return VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL_KHR;
        case D3D10_DSV_READ_ONLY_STENCIL:
          return VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL_KHR;
        case D3D10_DSV_READ_ONLY_DEPTH | D3D10_DSV_READ_ONLY_STENCIL:
          return VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
      }*/
	  return VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    }
    
    static HRESULT GetDescFromResource(
            ID3D10Resource*                   pResource,
            D3D10_DEPTH_STENCIL_VIEW_DESC*    pDesc);
    
    static HRESULT NormalizeDesc(
            ID3D10Resource*                   pResource,
            D3D10_DEPTH_STENCIL_VIEW_DESC*    pDesc);
    
  private:
    
    Com<D3D10Device>                  m_device;
    Com<ID3D10Resource>               m_resource;
    D3D10_DEPTH_STENCIL_VIEW_DESC     m_desc;
    Rc<DxvkImageView>                 m_view;
    
  };
  
}
