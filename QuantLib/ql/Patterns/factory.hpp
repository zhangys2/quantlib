
/*
 Copyright (C) 2000, 2001, 2002 RiskMap srl

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software developed by the QuantLib Group; you can
 redistribute it and/or modify it under the terms of the QuantLib License;
 either version 1.0, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 QuantLib License for more details.

 You should have received a copy of the QuantLib License along with this
 program; if not, please email ferdinando@ametrano.net

 The QuantLib License is also available at http://quantlib.org/license.html
 The members of the QuantLib Group are listed in the QuantLib License
*/
/*! \file factory.hpp
    \brief polymorphic factory pattern

    \fullpath
    ql/Patterns/%factory.hpp
*/

// $Id$

#ifndef quantlib_factory_h
#define quantlib_factory_h

#include <ql/qldefines.hpp>
#include <string>
#include <map>

namespace QuantLib {

    namespace Patterns {

        //! polymorphic object factory
        /*! This class is a reworked version of the polymorphic factory
            implemented in Bruce Eckel, Thinking in Patterns
            (http://www.bruceeckel.com).

            The class <tt>Type</tt> must define a type
            <tt>Type::factory</tt>.
            Instances of the latter must implement a method
            \code
            Type create() const;
            \endcode
            which returns a properly initialized instance of
            <tt>Type</tt>

            Such factories are stored in a <tt>Factory</tt> instance
            each with a corresponding tag. The latter can be used to
            request the creation of the corresponding object.
        */
        template <class Type>
        class Factory {
          public:
            typedef typename Type::factory factory_type;
          private:
            typedef std::map<std::string,Handle<factory_type> > map_type;
          public:
            //! adds a factory with the corresponding tag
            void add(const std::string& tag,
                     const Handle<factory_type>& factory) {
                factories_[tag] = factory;
            }
            //! creates an object
            /*! The object creation is delegated to the factory
                previously stored with the passed tag.
            */
            Type create(const std::string& tag) const {
                map_type::const_iterator i = factories_.find(tag);
                QL_REQUIRE(i != factories_.end(),
                           "factory called with unknown tag (" + tag + ")");
                return i->second->create();
            }
          private:
            map_type factories_;
        };

    }

}


#endif
