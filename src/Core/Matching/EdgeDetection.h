/**
 * This file is part of the IC reverse engineering tool Degate.
 *
 * Copyright 2008, 2009, 2010 by Martin Schobert
 * Copyright 2019-2020 Dorian Bachelot
 *
 * Degate is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * Degate is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with degate. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __EDGEDETECTION_H__
#define __EDGEDETECTION_H__

#include "Core/Image/Image.h"
#include "Core/Image/Processor/IPPipe.h"
#include "Core/Image/ImageHelper.h"

#include "Core/Image/Processor/IPCopy.h"
#include "Core/Image/Processor/IPConvolve.h"
#include "Core/Image/Processor/IPNormalize.h"
#include "Core/Image/Processor/IPThresholding.h"
#include "Core/Image/Manipulation/ImageManipulation.h"
#include "Core/Image/Processor/IPImageWriter.h"

namespace degate
{
	class EdgeDetection
	{
	private:

		IPPipe pipe;

		unsigned int min_x, max_x, min_y, max_y;
		unsigned int median_filter_width;

		unsigned int blur_kernel_size, border;
		double sigma;

		TileImage_GS_DOUBLE_shptr i1, i2; // edge images (x direction and y direction)

		std::string directory; // path for storing debug images
		bool has_path;

	public:

		void setup_pipe();


		unsigned int get_width() const;
		unsigned int get_height() const;

		void set_directory(std::string const& path);

		std::string get_directory() const;

		bool has_directory() const;

		void run_edge_detection(ImageBase_shptr in);

		TileImage_GS_DOUBLE_shptr get_horizontal_edges();
		TileImage_GS_DOUBLE_shptr get_vertical_edges();

		TileImage_GS_DOUBLE_shptr get_edge_magnitude_image(TileImage_GS_DOUBLE_shptr probability_map);

		TileImage_GS_DOUBLE_shptr get_edge_image(TileImage_GS_DOUBLE_shptr probability_map);


	public:

		EdgeDetection(unsigned int min_x, unsigned int max_x,
                      unsigned int min_y, unsigned int max_y,
                      unsigned int median_filter_width = 3,
                      unsigned int blur_kernel_size = 10,
                      double sigma = 0.5);

		virtual ~EdgeDetection();

		unsigned int get_border() const;
	};
}


#endif
