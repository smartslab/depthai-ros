#include "depthai/pipeline/datatype/SystemInformation.hpp"
#include "depthai_ros_driver/dai_nodes/base_node.hpp"
#include "diagnostic_updater/diagnostic_updater.hpp"
namespace dai {
class Pipeline;
class Device;
class MessageQueue;
class ADatatype;
namespace node {
class SystemLogger;
class VideoEncoder;
}  // namespace node
}  // namespace dai
namespace rclcpp {
class Node;
class TimerBase;
}  // namespace rclcpp

namespace depthai_ros_driver {

namespace dai_nodes {
class SysLogger : public BaseNode {
   public:
    SysLogger(const std::string& daiNodeName, std::shared_ptr<rclcpp::Node> node, std::shared_ptr<dai::Pipeline> pipeline);
    ~SysLogger();
    void setupQueues(std::shared_ptr<dai::Device> device) override;
    void setNames() override;

   private:
    std::string sysInfoToString(const dai::SystemInformation& sysInfo);
    void produceDiagnostics(diagnostic_updater::DiagnosticStatusWrapper& stat);
    std::shared_ptr<diagnostic_updater::Updater> updater;
    std::shared_ptr<dai::node::SystemLogger> sysNode;
    std::shared_ptr<dai::MessageQueue> loggerQ;
    std::string loggerQName;
};
}  // namespace dai_nodes
}  // namespace depthai_ros_driver
