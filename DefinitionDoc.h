/*
 * DefinitionDoc.h
 *
 *  Created on: Oct 17, 2014
 *      Author: jandres
 */

#ifndef DEFINITIONDOC_H_
#define DEFINITIONDOC_H_

/*! \page tileCoding Tile Coding
 * \tableofcontents
 * \section section01 Coarse Coding
 *  Suppose we have a two-dimensional state-action space more generally called <i>feature</i>.
 *  Each dimension is in Real Domain \f$\mathbb{R}\f$. Since its in Real Domain
 *  \f$\mathbb{R}\f$, its continuous and thus harder to represent it with
 *  individual state-action pair. Consider for example a state-space in domain
 *  \f$[0.0, 1.0]\f$. How would the state-action space be represented? It could be in
 *  0.1 increment giving us \f$10\times 10\f$ state space or 0.2 increment,
 *  giving us \f$5\times 5\f$ state space. How would we generalize between
 *  intermediate points? All of these problems are addressed by Coarse Coding.
 *
 *  Coarse Coding allows us to handle the division into finite state space as
 *  well generalization around intermediate states (since continuous, there's
 *  infinite intermediate states). Suppose one of the state space is \f$x\f$
 *  and \f$y\f$.
 *
 *  \image html Documentation/tileCode01.png
 *
 *  In the image above, the state space have circles scattered around them.
 *  For \f$x\f$, all the circles that intersect \f$x\f$ are generalized, this
 *  includes \f$y\f$. The bigger the radius of the circle, the bigger the
 *  generalization. This is Coarse Coding.
 *
 * \section section02 Tile Coding
 * Tile Coding is a type of Coarse Coding. For a given state-space or <i>feature</i>,
 * we create a number of copies, called <i>tiling</i>. For easier computation and
 * elaboration, grid-like <i>tilings</i> are used. For example for a 1 dimensional state
 * and 1 dimensional action, the state-action space will be 2 dimensional. This
 * will be represented via the following,
 *
 * \image html Documentation/tileCode02.png
 *
 * For each state-action pair, it is represented by a vertex. One could say that
 * the state and action are divided into 5 state space. Each square, represent
 * immediate states known as a <i>tile</i> of the <i>tiling</i> grid. <i>Tilings</i>,
 * represent a number of <i>tiling</i> offseted by different amount. The number of <i>tiling</i>
 * determines the resolution of final estimate (Quality of estimate). Compared with the example
 * in Coarse Coding, the randomized tiling is considered the random placement of circles.
 * This is elaborated by the image,
 *
 * \image html Documentation/tileCode03.png
 *
 * By default, the length of the generalization is the 1 tile away. For example, for a state in coordinate
 * (0,0) in the example above, the generalization limit is (0.99, 99), (0.0, 0.99), (0.99, 0.0) boundaries.
 *
 * \section section03 Implementation Example
 * Work In Progress.
 */

#endif /* DEFINITIONDOC_H_ */
