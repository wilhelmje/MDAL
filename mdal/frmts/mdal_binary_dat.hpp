/*
 MDAL - Mesh Data Abstraction Library (MIT License)
 Copyright (C) 2018 Peter Petrik (zilolv at gmail dot com)
*/

#ifndef MDAL_BINARY_DAT_HPP
#define MDAL_BINARY_DAT_HPP

#include <string>
#include <vector>
#include <memory>
#include <iosfwd>
#include <iostream>
#include <fstream>

#include "mdal_data_model.hpp"
#include "mdal.h"
#include "mdal_driver.hpp"

namespace MDAL
{

  class DriverBinaryDat: public Driver
  {
    public:
      DriverBinaryDat();
      ~DriverBinaryDat( ) override;
      DriverBinaryDat *create() override;

      bool canReadDatasets( const std::string &uri ) override;
      void load( const std::string &datFile, Mesh *mesh ) override;
      bool persist( DatasetGroup *group ) override;

      std::string writeDatasetOnFileSuffix() const override;

    private:

      //! Gets maximum (native) index.
      //! For meshes without indexing gap it is vertexCount - 1
      //! For some HYDRO_AS-2D meshes with indexing gaps, it returns
      //! maximum native index of the vertex in defined in the mesh
      size_t maximumId( const Mesh *mesh ) const;

      bool readVertexTimestep( const Mesh *mesh,
                               std::shared_ptr<DatasetGroup> group,
                               std::shared_ptr<DatasetGroup> groupMax,
                               RelativeTimestamp time,
                               bool hasStatus,
                               int sflg,
                               std::ifstream &in );

      std::string mDatFile;
  };

} // namespace MDAL
#endif //MDAL_BINARY_DAT_HPP
