#pragma once

#include <memory>
#include <string>

#include "depthai/common/CameraBoardSocket.hpp"
#include "depthai/pipeline/Node.hpp"
#include "depthai_ros_driver/utils.hpp"
#include "rclcpp/logger.hpp"

namespace dai {
class Pipeline;
class Device;
namespace node {
class VideoEncoder;
}  // namespace node
}  // namespace dai

namespace rclcpp {
class Node;
class Parameter;
}  // namespace rclcpp

namespace depthai_ros_driver {
namespace dai_nodes {
namespace sensor_helpers {
class ImagePublisher;
struct VideoEncoderConfig;
}  // namespace sensor_helpers
class BaseNode {
   public:
    /**
     * @brief      Constructor of the class BaseNode. Creates a node in the pipeline.
     *
     * @param[in]  daiNodeName  The dai node name
     * @param      node         The node
     * @param      pipeline     The pipeline
     */
    BaseNode(const std::string& daiNodeName, std::shared_ptr<rclcpp::Node> node, std::shared_ptr<dai::Pipeline> pipeline);
    virtual ~BaseNode();
    virtual void updateParams(const std::vector<rclcpp::Parameter>& params);
    virtual void link(dai::Node::Input in, int linkType = 0);
    virtual dai::Node::Input& getInput(int linkType = 0);
    virtual dai::Node::Input getInputByName(const std::string& name = "");
    virtual std::vector<std::shared_ptr<sensor_helpers::ImagePublisher>> getPublishers();
    virtual void setupQueues(std::shared_ptr<dai::Device> device) = 0;
    /**
     * @brief      Sets the names of the queues.
     */
    virtual void setNames() = 0;
    /**
     * @brief      Link inputs and outputs. Creates Publishers.
     *
     * @param      pipeline  The pipeline
     */
    virtual void setOutputs(std::shared_ptr<dai::Pipeline> pipeline);
    std::shared_ptr<sensor_helpers::ImagePublisher> createPublisher(std::shared_ptr<dai::Pipeline> pipeline,
                                                                const std::string& qName,
                                                                dai::Node::Output& out,
                                                                bool isSynced = false,
                                                                const utils::VideoEncoderConfig& encoderConfig = {});
    void setNodeName(const std::string& daiNodeName);
    void setROSNodePointer(std::shared_ptr<rclcpp::Node> node);
    /**
     * @brief      Gets the ROS node pointer.
     *
     * @return     The ROS node pointer.
     */
    std::shared_ptr<rclcpp::Node> getROSNode();
    /**
     * @brief      Gets the name of the node.
     *
     * @return     The name.
     */
    std::string getName();
    /**
     * @brief    Append ROS node name to the frameName given.
     *
     * @param[in]  frameName  The frame name
     */
    std::string getTFPrefix(const std::string& frameName = "");
    /**
     * @brief    Append ROS node name to the frameName given and append optical frame suffix to it.
     *
     * @param[in]  frameName  The frame name
     */
    std::string getOpticalTFPrefix(const std::string& frameName = "");
    bool ipcEnabled();
    std::string getSocketName(dai::CameraBoardSocket socket);
    bool rsCompabilityMode();
    rclcpp::Logger getLogger();

   private:
    std::shared_ptr<rclcpp::Node> baseNode;
    std::string baseDAINodeName;
    bool intraProcessEnabled;
    rclcpp::Logger logger;
};
}  // namespace dai_nodes
}  // namespace depthai_ros_driver
