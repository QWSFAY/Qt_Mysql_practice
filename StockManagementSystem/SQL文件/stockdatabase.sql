/*
 Navicat Premium Data Transfer

 Source Server         : localhost_3306
 Source Server Type    : MySQL
 Source Server Version : 80022 (8.0.22)
 Source Host           : localhost:3306
 Source Schema         : stockdatabase

 Target Server Type    : MySQL
 Target Server Version : 80022 (8.0.22)
 File Encoding         : 65001

 Date: 21/06/2025 21:28:10
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for commoditydatatable
-- ----------------------------
DROP TABLE IF EXISTS `commoditydatatable`;
CREATE TABLE `commoditydatatable`  (
  `StockId` int NOT NULL COMMENT '编号',
  `StockName` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '名字',
  `StockAmount` int NULL DEFAULT NULL COMMENT '数量',
  `StockunitPrice` decimal(10, 2) NOT NULL COMMENT '价格',
  `Supplier` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '供应人',
  `Directot` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '负责人',
  `WarehousTime` datetime NULL DEFAULT NULL,
  `DeliveryTime` datetime NULL DEFAULT NULL,
  `Remarks` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '备注\r\n',
  PRIMARY KEY (`StockId`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of commoditydatatable
-- ----------------------------
INSERT INTO `commoditydatatable` VALUES (1001, '百事可乐', 100, 6.00, 'BS', 'Q', '2025-06-21 20:09:34', '2025-06-21 20:09:36', '饮品');
INSERT INTO `commoditydatatable` VALUES (1002, '芙蓉王', 80, 1000.00, ' 王源', 'Q', '2025-06-21 20:11:07', '2025-06-21 20:11:10', '香烟');

SET FOREIGN_KEY_CHECKS = 1;
