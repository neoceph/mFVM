
Theories and Equations
=======================

**Discretization of the diffusion equation**


The steady diffusion equation is given by:

.. math::
      \nabla \cdot \left( \Gamma \nabla \phi \right) + S_\varphi = 0

where :math:`\Gamma` is the diffusion coefficient and :math:`S_\varphi` is the source.

Considering a 1D domain, the diffusion equation can be discretized as follows:

.. math:: 
      \frac{d}{dx} \left( \Gamma \frac{d \phi}{dx} \right) + S_\varphi = 0

Integrating over a control volume :math:`\Delta V` and applying the divergence theorem, we obtain:

.. math:: 
      \int_{\Delta V} \frac{d}{dx} \left( \Gamma \frac{d \phi}{dx} \right) dV + \int_{\Delta V} S_\varphi dV = 0
.. math:: 
      \int_{\partial A} n \cdot\left(\Gamma \frac{d \phi}{dx}\right) dA + \int_{\Delta V} S_\varphi dV = 0
.. math:: 
      \left(\Gamma \frac{d \phi}{dx}\right)_{east} - \left(\Gamma \frac{d \phi}{dx}\right)_{west} + S_\varphi \Delta V = 0
.. math:: 
      \Gamma\left(\frac{\phi_{E}-\phi_{P}}{dx_{EP}}\right) - \Gamma\left(\frac{\phi_{P}-\phi_{W}}{dx_{WP}}\right) = 0
      :label: eq:pfx
.. math:: 
      \Gamma\left(\frac{\phi_{E}-\phi_{P}}{dx_{EP}}\right) - \Gamma\left(\frac{\phi_{P}-\phi_{W}}{dx_{WP}}\right) = 0      
      :label: eq:pfx