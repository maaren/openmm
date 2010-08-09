/* -------------------------------------------------------------------------- *
 *                                   OpenMM                                   *
 * -------------------------------------------------------------------------- *
 * This is part of the OpenMM molecular simulation toolkit originating from   *
 * Simbios, the NIH National Center for Physics-Based Simulation of           *
 * Biological Structures at Stanford, funded under the NIH Roadmap for        *
 * Medical Research, grant U54 GM072970. See https://simtk.org.               *
 *                                                                            *
 * Portions copyright (c) 2008 Stanford University and the Authors.           *
 * Authors: Peter Eastman                                                     *
 * Contributors:                                                              *
 *                                                                            *
 * Permission is hereby granted, free of charge, to any person obtaining a    *
 * copy of this software and associated documentation files (the "Software"), *
 * to deal in the Software without restriction, including without limitation  *
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,   *
 * and/or sell copies of the Software, and to permit persons to whom the      *
 * Software is furnished to do so, subject to the following conditions:       *
 *                                                                            *
 * The above copyright notice and this permission notice shall be included in *
 * all copies or substantial portions of the Software.                        *
 *                                                                            *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    *
 * THE AUTHORS, CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,    *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR      *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE  *
 * USE OR OTHER DEALINGS IN THE SOFTWARE.                                     *
 * -------------------------------------------------------------------------- */

#include "internal/AmoebaGeneralizedKirkwoodForceImpl.h"
#include "openmm/internal/ContextImpl.h"
#include "amoebaKernels.h"

using namespace OpenMM;
using std::vector;

AmoebaGeneralizedKirkwoodForceImpl::AmoebaGeneralizedKirkwoodForceImpl(AmoebaGeneralizedKirkwoodForce& owner) : owner(owner) {
}

void AmoebaGeneralizedKirkwoodForceImpl::initialize(ContextImpl& context) {
    kernel = context.getPlatform().createKernel(CalcAmoebaGeneralizedKirkwoodForceKernel::Name(), context);
    if (owner.getNumParticles() != context.getSystem().getNumParticles())
        throw OpenMMException("AmoebaGeneralizedKirkwoodForce must have exactly as many particles as the System it belongs to.");
    dynamic_cast<CalcAmoebaGeneralizedKirkwoodForceKernel&>(kernel.getImpl()).initialize(context.getSystem(), owner);
}

void AmoebaGeneralizedKirkwoodForceImpl::calcForces(ContextImpl& context) {
    dynamic_cast<CalcAmoebaGeneralizedKirkwoodForceKernel&>(kernel.getImpl()).executeForces(context);
}

double AmoebaGeneralizedKirkwoodForceImpl::calcEnergy(ContextImpl& context) {
    return dynamic_cast<CalcAmoebaGeneralizedKirkwoodForceKernel&>(kernel.getImpl()).executeEnergy(context);
}

std::vector<std::string> AmoebaGeneralizedKirkwoodForceImpl::getKernelNames() {
    std::vector<std::string> names;
    names.push_back(CalcAmoebaGeneralizedKirkwoodForceKernel::Name());
    return names;
}