/*
 * Copyright 2016 The Cartographer Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "cartographer/mapping/trajectory_builder_interface.h"

#include "cartographer/mapping/local_slam_result_data.h"
#include "cartographer/mapping_2d/local_trajectory_builder_options.h"
#include "cartographer/mapping_3d/local_trajectory_builder_options.h"

namespace cartographer {
namespace mapping {

proto::TrajectoryBuilderOptions CreateTrajectoryBuilderOptions(
    common::LuaParameterDictionary* const parameter_dictionary) {
  proto::TrajectoryBuilderOptions options;
  *options.mutable_trajectory_builder_2d_options() =
      mapping_2d::CreateLocalTrajectoryBuilderOptions(
          parameter_dictionary->GetDictionary("trajectory_builder_2d").get());
  *options.mutable_trajectory_builder_3d_options() =
      mapping_3d::CreateLocalTrajectoryBuilderOptions(
          parameter_dictionary->GetDictionary("trajectory_builder_3d").get());
  options.set_pure_localization(
      parameter_dictionary->GetBool("pure_localization"));
  return options;
}

proto::SensorId ToProto(const TrajectoryBuilderInterface::SensorId& sensor_id) {
  proto::SensorId sensor_id_proto;
  switch (sensor_id.type) {
    case TrajectoryBuilderInterface::SensorId::SensorType::RANGE:
      sensor_id_proto.set_type(proto::SensorId::RANGE);
      break;
    case TrajectoryBuilderInterface::SensorId::SensorType::IMU:
      sensor_id_proto.set_type(proto::SensorId::IMU);
      break;
    case TrajectoryBuilderInterface::SensorId::SensorType::ODOMETRY:
      sensor_id_proto.set_type(proto::SensorId::ODOMETRY);
      break;
    case TrajectoryBuilderInterface::SensorId::SensorType::FIXED_FRAME_POSE:
      sensor_id_proto.set_type(proto::SensorId::FIXED_FRAME_POSE);
      break;
    case TrajectoryBuilderInterface::SensorId::SensorType::LANDMARK:
      sensor_id_proto.set_type(proto::SensorId::LANDMARK);
      break;
    case TrajectoryBuilderInterface::SensorId::SensorType::LOCAL_SLAM_RESULT:
      sensor_id_proto.set_type(proto::SensorId::LOCAL_SLAM_RESULT);
      break;
    default:
      LOG(FATAL) << "Unsupported sensor type.";
  }
  sensor_id_proto.set_id(sensor_id.id);
  return sensor_id_proto;
}

TrajectoryBuilderInterface::SensorId FromProto(
    const proto::SensorId& sensor_id_proto) {
  TrajectoryBuilderInterface::SensorId sensor_id;
  switch (sensor_id_proto.type()) {
    case proto::SensorId::RANGE:
      sensor_id.type = TrajectoryBuilderInterface::SensorId::SensorType::RANGE;
      break;
    case proto::SensorId::IMU:
      sensor_id.type = TrajectoryBuilderInterface::SensorId::SensorType::IMU;
      break;
    case proto::SensorId::ODOMETRY:
      sensor_id.type =
          TrajectoryBuilderInterface::SensorId::SensorType::ODOMETRY;
      break;
    case proto::SensorId::FIXED_FRAME_POSE:
      sensor_id.type =
          TrajectoryBuilderInterface::SensorId::SensorType::FIXED_FRAME_POSE;
      break;
    case proto::SensorId::LANDMARK:
      sensor_id.type =
          TrajectoryBuilderInterface::SensorId::SensorType::LANDMARK;
      break;
    case proto::SensorId::LOCAL_SLAM_RESULT:
      sensor_id.type =
          TrajectoryBuilderInterface::SensorId::SensorType::LOCAL_SLAM_RESULT;
      break;
    default:
      LOG(FATAL) << "Unsupported sensor type.";
  }
  sensor_id.id = sensor_id_proto.id();
  return sensor_id;
}

}  // namespace mapping
}  // namespace cartographer
