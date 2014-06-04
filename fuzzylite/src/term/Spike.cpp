// #BEGIN_LICENSE
// fuzzylite: a fuzzy logic control library in C++
// Copyright (C) 2014  Juan Rada-Vilela
// 
// This file is part of fuzzylite.
//
// fuzzylite is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// fuzzylite is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with fuzzylite.  If not, see <http://www.gnu.org/licenses/>.
// #END_LICENSE

#include "fl/term/Spike.h"

namespace fl {

    Spike::Spike(const std::string& name, scalar center, scalar width)
    : Term(name), _center(center), _width(width) {
    }

    Spike::~Spike() {

    }

    std::string Spike::className() const {
        return "Spike";
    }

    std::string Spike::parameters() const {
        return Op::join(2, " ", _center, _width);
    }

    void Spike::configure(const std::string& parameters) {
        if (parameters.empty()) return;
        std::vector<std::string> values = Op::split(parameters, " ");
        std::size_t required = 2;
        if (values.size() < required) {
            std::ostringstream ex;
            ex << "[configuration error] term <" << className() << ">"
                    << " requires <" << required << "> parameters";
            throw fl::Exception(ex.str(), FL_AT);
        }
        setCenter(Op::toScalar(values.at(0)));
        setWidth(Op::toScalar(values.at(1)));
    }

    scalar Spike::membership(scalar x) const {
        if (fl::Op::isNaN(x)) return fl::nan;
        return std::exp(-std::fabs(10.0 / _width * (x - _center)));
    }

    void Spike::setCenter(scalar center) {
        this->_center = center;
    }

    scalar Spike::getCenter() const {
        return this->_center;
    }

    void Spike::setWidth(scalar width) {
        this->_width = width;
    }

    scalar Spike::getWidth() const {
        return this->_width;
    }

    Spike* Spike::clone() const {
        return new Spike(*this);
    }

    Term* Spike::constructor() {
        return new Spike;
    }
}
