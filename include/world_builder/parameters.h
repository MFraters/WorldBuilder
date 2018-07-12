/*
  Copyright (C) 2018 by the authors of the World Builder code.

  This file is part of the World Builder.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation, either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef _world_builder_parameters_h
#define _world_builder_parameters_h

#include <string>
#include <vector>
#include <unordered_map>

#include <boost/property_tree/ptree.hpp>

#include <world_builder/types/interface.h>
#include <world_builder/types/unsigned_int.h>
#include <world_builder/types/double.h>
#include <world_builder/types/string.h>
#include <world_builder/types/point.h>
#include <world_builder/types/array.h>
#include <world_builder/types/list.h>


//#include <world_builder/coordinate_systems/interface.h>
//#include <world_builder/features/interface.h>


using boost::property_tree::ptree;

namespace WorldBuilder
{

  namespace Features
  {
    class Interface;
  }

  namespace CoordinateSystems
  {
    class Interface;
  }

  class World;

  class Parameters
  {
    public:
      /**
       * Constructor
       */
      Parameters(std::string &filename, World &);

      /**
       * Destructor
       */
      ~Parameters();

      bool load_entry(const std::string &name, const bool required, const Types::Interface &type);

      bool set_entry(const std::string &name, const Types::Interface &type);

      void enter_subsection(const std::string name);

      void leave_subsection();

      unsigned int get_unsigned_int(const std::string &name) const;

      double get_double(const std::string &name) const;

      std::string get_string(const std::string &name) const;

      // get_array(const std::string& name);

      template<int dim>
      Point<dim> get_point(const std::string &name) const;

      // TODO:
      //template<class T>
      //T get(const std::string &name);


      /**
       * Returns the array with pointers to the base class Interface. The
       * caller is not responible for the classes pointed at in the return
       * vector or has ownership on them. So give raw pointers.
       */
      const Types::Array &get_array(const std::string &name) const;

      template<class T>
      const std::vector<T*> get_array(const std::string &name) const;

      World &world;

      /**
       * These are the top level parameters
       */
      // int dim;
      //std::vector<std::array<double,2> > cross_section;
      //std::vector<double> surface_coord_conversions;
      //std::vector<double> surface_rotation_point;
      //double surface_rotation_angle;
      //unsigned int minimum_parts_per_distance_unit;
      //double minimum_distance_points;
      const std::string path_seperator = ".";
      std::vector<std::string> path;

      /**
       * the boost property tree, used to read in the data from a json file.
       */
      ptree tree;

      /**
       * contains a pointer to the a part of the tree. This variable is not
       * repsonsible for the tree, so using a raw pointer.
       */
      ptree *local_tree;

      std::unordered_map<std::string,unsigned int> string_to_type_map;
      std::vector<Types::UnsignedInt> vector_unsigned_int;
      std::vector<Types::Double> vector_double;
      std::vector<Types::String> vector_string;
      std::vector<Types::Array> vector_array;
      std::vector<Types::List> vector_list;
      std::vector<Types::Point<2> > vector_point_2d;
      std::vector<Types::Point<3> > vector_point_3d;


      /**
       * contains all the plugins.
       */
      std::vector<std::unique_ptr<WorldBuilder::Features::Interface> > features;

      // coordinate system
      std::unique_ptr<WorldBuilder::CoordinateSystems::Interface> coordinate_system;

      std::string get_current_path() const;

      std::string get_current_path_without_arrays() const;

    private:
      bool load_entry(std::vector<std::string> &path, const std::string &name, const bool required, const Types::Interface &type, unsigned int &location);
      bool set_entry(std::vector<std::string> &path, const std::string &name, const Types::Interface &type, unsigned int &location);



      /**
       * No reference, but copy to be able to change it locally
       */
      std::string get_current_path(std::vector<std::string> &path) const;

      /**
       * No reference, but copy to be able to change it locally
       */
      std::string get_current_path_without_arrays(std::vector<std::string> &path) const;
  };
}
#endif
