/**
 * Provides the ExternalBoundary class.
 * @file externalboundary.hpp
 *
 * @author Harrison Steggles
 *
 * @date 29/01/2014, the first version.
 */

#ifndef EXTERNAL_HPP_
#define EXTERNAL_HPP_

#include "boundary.hpp"
/**
 * @class ExternalBoundary
 * @brief Holds a Grid3D face ExternalBoundary to apply boundary conditions during integration.
 * The ExternalBoundary class inherits from the Boundary class. ExternalBoundary instances provide GridCell instances that buffer a grid
 * face from unsimulated regions. ExternalBoundary::applyBC applies boundary conditions to the contained GridCell instances.
 * Grid3D handles the binding of an ExternalBoundary to its grid of GridCell objects.
 * @see Boundary
 * @see Grid3D
 * @see GridCell
 *
 * @version 0.3, 29/01/2014
 */
class ExternalBoundary : public Boundary {
public:
	Condition bc;
	/**
	 * @brief ExternalBoundary constructor.
	 * @param face
	 * The face of the grid that the boundary is connected to (face < 3: left face, else: right face).
	 * @param bcond
	 * The boundary condition that must be applied to this boundary at the start of each hydro/radiation update step.
	 * @param gptr
	 * A pointer to the Grid3D object that the Boundary should be linked to with Grid3D::boundaryLink(Boundary*).
	 */
	ExternalBoundary(int face, Condition bcond, Grid3D* gptr);
	/**
	 * @brief Applies the boundary condition that was passed to this object through its constructor.
	 */
	void applyBC();
};



#endif /* EXTERNAL_HPP_ */
