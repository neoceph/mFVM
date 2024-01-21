
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
      \left(\Gamma A  \frac{d \phi}{dx}\right)_{east} - \left(\Gamma A \frac{d \phi}{dx}\right)_{west} + \bar{S_\varphi} \Delta V = 0
In the equation above :math:`\bar{S_\varphi}` is the average value of source :math:`S` over the control volume. Considering the source term as a function of the dependent variable :math:`\phi` as :math:`\bar{S}\Delta V = S_u + S_p\phi_P`, we can write:

.. math:: 
      \Gamma_e A_e \left(\frac{\phi_{E}-\phi_{P}}{dx_{PE}}\right) - \Gamma_w A_w\left(\frac{\phi_{P}-\phi_{W}}{dx_{WP}}\right) + (S_u + S_p\phi_P) = 0
      :label: eq:pfx
Rearranging the terms to separate the independent variables

.. math::
      - \left(\frac{\Gamma_w A_w}{dx_{WP}}\right)\phi_W + \left(\frac{\Gamma_e A_e}{dx_{PE}} + \frac{\Gamma_w A_w}{dx_{WP}} - S_P \right)\phi_P - \left(\frac{\Gamma_e A_e}{dx_{PE}}\right)\phi_E = S_u
      :label: eq:pfy

Boundary Conditions
^^^^^^^^^^^^^^^^^^^
There are different scenarios for the boundary conditions. The boundary conditions can be classified into two categories:

1. Dirichlet boundary condition (Temperature specified)
2. Neumann boundary condition (Heat flux specified)

Dirichlet boundary condition
----------------------------
In this case, the temperature is specified at the boundary. The temperature is specified at the boundary and hence additional equation is not required. On the west boundary, there isn't any control volume to the west, and hence the boundary needs a special treatment in estimating the flux on the west face of the control volume located at the west boundary.

Considering equation (1) and replacing :math:`\phi_W` with :math:`\phi_W^B` and the control volume width :math:`dx_{WP}` with :math:`dx_{WP}^B = dx_{W^BP} = \Delta x` or :math:`\frac{dx}{2}` (depending on whether cell center (:math:`\Delta x`) is at the boundary or the cell face (:math:`\frac{dx}{2}`) is at boundary), we can rewrite the equation as:

.. math:: 
      \Gamma_e A_e \left(\frac{\phi_{E}-\phi_{P}}{dx_{PE}}\right) - \Gamma_w A_w\left(\frac{\phi_{P}-\phi^B_{W}}{dx_{W^BP}}\right) + (S_u + S_p\phi_P) = 0

Rearranging the terms give out the alternate form of equation (2) as:

**West Boundary**

.. math::
      0\cdot\phi_W + \left(\frac{\Gamma_e A_e}{dx_{PE}} + \frac{\Gamma_w A_w}{dx_{W^BP}} - S_P \right)\phi_P - \left(\frac{\Gamma_e A_e}{dx_{PE}}\right)\phi_E = S_u + \left(\frac{\Gamma_w A_w}{dx_{W^BP}}\right)\phi^B_W
      :label: eq:pfy

**East Boundary**

Similarly for the east boundary, we have:

.. math::
      - \left(\frac{\Gamma_w A_w}{dx_{WP}}\right)\phi_W + \left(\frac{\Gamma_e A_e}{dx_{PE^B}} + \frac{\Gamma_w A_w}{dx_{WP}} - S_P \right)\phi_P - 0\cdot\phi_E = S_u + \left(\frac{\Gamma_E A_E}{dx_{PE^B}}\right)\phi^B_E
      :label: eq:pfy

Neumann boundary condition
----------------------------

There are cases when the flux is specified at the boundary rather than a specified temperature. In such cases, the flux is specified at the boundary and hence additional equation is required. On the west boundary, there isn't any control volume of full size to the west, and hence the boundary needs a special treatment in estimating the flux on the west face of the control volume located at the west boundary. Considering the cell center lying on the boundary We only have a half of the control volume where the cell center of half plane lies on the west boundary. (Patankar figure 4.4).
Considering a convective heat flux as specified with equation

.. math:: 
      q_{W^B} = -h (\phi_\infty - \phi_{W^B}) = h (\phi_{W^B} - \phi_\infty)

where :math:`h` is the convective coefficient and :math:`\phi_\infty` is the temperature of the ambient and :math:`\phi_{W^B}` is the temperature. Considering the flux coming in from the west boundary and leaving the east cell face, we can start by writing the equation as:

.. math:: 
      -q_{W^B} + q_E + (S_u + S_P \phi_P)= 0

.. math:: 
      -h (\phi_{W^B} - \phi_\infty) + \Gamma_e A_e \left(\frac{\phi_E - \phi_{W^B}}{dx_{{W^B}E}}\right) + (S_u + S_P \phi_{{W^B}E})= 0
rearrenging the terms, we get:

.. math:: 
      \left(h+\frac{\Gamma_e A_e}{dx_{{W^B}E}} - S_P\right)\phi_{W^B} - \frac{\Gamma_e A_e}{dx_{{W^B}E}}\phi_{E} = h\phi_\infty + S_u
comparing with equation (2), we get:

**West Boundary**

.. math:: 
      0 \cdot \phi_W + \left(h+\frac{\Gamma_e A_e}{dx_{PE}} - S_P\right)\phi_P - \frac{\Gamma_e A_e}{dx_{PE}}\phi_{E} = h\phi_\infty + S_u
      :label: eq:pfy

**East Boundary**

In a similar fashion, for the east boundary, we will have

.. math:: 
      - \frac{\Gamma_w A_w}{dx_{PW}}\phi_{W} + \left(h+\frac{\Gamma_e A_e}{dx_{PE}} - S_P\right)\phi_P + 0 \cdot \phi_E= h\phi_\infty + S_u
      :label: eq:pfy