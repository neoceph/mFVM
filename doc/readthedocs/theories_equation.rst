
Theories and Equations
=======================

**Discretization of the diffusion equation**

:ref:`Boundary Condition<boundary-conditions>`
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
      \left(\Gamma A  \frac{d \phi}{dx}\right)_{east} - \left(\Gamma A \frac{d \phi}{dx}\right)_{west} + \bar{S_\varphi} \Delta V = 0
In the equation above :math:`\bar{S_\varphi}` is the average value of source :math:`S` over the control volume. Considering the source term as a function of the dependent variable :math:`\phi` as :math:`\bar{S}\Delta V = S_u + S_p\phi_P`, we can write:

.. math:: 
      \Gamma_e A_e \left(\frac{\phi_{E}-\phi_{P}}{dx_{PE}}\right) - \Gamma_w A_w\left(\frac{\phi_{P}-\phi_{W}}{dx_{WP}}\right) + (S_u + S_p\phi_P) = 0
      :label: eq:pfx
Rearranging the terms to separate the independent variables

.. math::
      - \left(\frac{\Gamma_w A_w}{dx_{WP}}\right)\phi_W + \left(\frac{\Gamma_e A_e}{dx_{PE}} + \frac{\Gamma_w A_w}{dx_{WP}} - S_P \right)\phi_P - \left(\frac{\Gamma_e A_e}{dx_{PE}}\right)\phi_E = S_u
      :label: eq:pfy
.. _boundary-conditions:
Boundary Conditions
^^^^^^^^^^^^^^^^^^^
On the west boundary, there isn't any control volume to the west, and hence the boundary needs a special treatment in estimating the flux on the west face of the control volume located at the west boundary.

Considering equation (1) and replacing :math:`\phi_W` with :math:`\phi_W^B` and the control volume width :math:`dx_{WP}` with :math:`dx_{WP}^B = dx_{W^BP} = \frac{dx}{2}`, we can rewrite the equation as:

.. math:: 
      \Gamma_e A_e \left(\frac{\phi_{E}-\phi_{P}}{dx_{PE}}\right) - \Gamma_w A_w\left(\frac{\phi_{P}-\phi^B_{W}}{dx_{W^BP}}\right) + (S_u + S_p\phi_P) = 0
Rearranging the terms give out the alternate form of equation (2) as:

.. math::
      0\cdot\phi_W + \left(\frac{\Gamma_e A_e}{dx_{PE}} + \frac{\Gamma_w A_w}{dx_{W^BP}} - S_P \right)\phi_P - \left(\frac{\Gamma_e A_e}{dx_{PE}}\right)\phi_E = S_u + \left(\frac{\Gamma_w A_w}{dx_{W^BP}}\right)\phi^B_W

Similarly for the east boundary, we have:

.. math::
      - \left(\frac{\Gamma_w A_w}{dx_{WP}}\right)\phi_W + \left(\frac{\Gamma_e A_e}{dx_{PE^B}} + \frac{\Gamma_w A_w}{dx_{WP}} - S_P \right)\phi_P - 0\cdot\phi_E = S_u + \left(\frac{\Gamma_E A_E}{dx_{PE^B}}\right)\phi^B_E