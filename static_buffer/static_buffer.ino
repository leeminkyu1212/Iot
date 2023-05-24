
/* Edge Impulse ingestion SDK
 * Copyright (c) 2022 EdgeImpulse Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

/* Includes ---------------------------------------------------------------- */
#include <leeminkyu1212-project-1_inferencing.h>

static const float features[] = {
    4.0431, 0.1524, 0.1714, -0.0039, -0.0016, 0.0019, 0.0030, 0.0002, 0.0000, 0.0022, 0.0000, 0.0022, -0.3639, -0.9262, 3.6069, 0.5333, 0.5524, -0.0002, -0.0001, 0.0001, 0.0002, -0.0000, 0.0000, 0.0001, 0.0000, 0.0001, 0.2037, 2.1351, 3.5112, 0.0762, 0.0762, -0.0214, -0.0125, 0.0178, 0.0186, 0.0014, 0.0007, 0.0150, 0.0002, 0.0150, -0.1233, -1.5063, 3.5252, 0.5429, 0.4857, -0.0007, -0.0002, 0.0001, 0.0007, 0.0000, -0.0000, 0.0004, 0.0000, 0.0004, -0.1612, 2.0983, 4.0472, 0.0667, 0.0667, -0.0225, -0.0167, 0.0138, 0.0250, -0.0011, -0.0004, 0.0163, 0.0003, 0.0164, 0.1832, -1.3474, 3.7273, 0.5429, 0.5619, -0.0006, -0.0002, 0.0003, 0.0009, 0.0000, 0.0000, 0.0004, 0.0000, 0.0004, 0.1052, 0.9627, 4.0332, 0.0952, 0.0952, -0.0779, -0.0309, 0.0383, 0.0660, 0.0064, 0.0011, 0.0458, 0.0021, 0.0458, -0.3537, -0.8063, 3.6779, 0.5429, 0.5429, -0.0031, -0.0013, 0.0006, 0.0037, -0.0002, -0.0002, 0.0019, 0.0000, 0.0019, 0.7992, 2.4609, 3.9474, 0.0762, 0.0762, -0.1961, -0.1598, 0.1503, 0.2747, -0.0065, 0.0066, 0.1654, 0.0276, 0.1656, 0.2520, -1.4017, 3.8020, 0.5905, 0.5905, -0.0064, -0.0014, 0.0016, 0.0071, -0.0000, 0.0001, 0.0037, 0.0000, 0.0037, 0.2143, 1.1847, 4.0613, 0.0857, 0.0857, -0.2762, -0.2153, 0.1659, 0.3268, -0.0343, -0.0059, 0.2073, 0.0434, 0.2073, 0.2312, -1.3404, 3.3871, 0.5048, 0.5429, -0.0087, -0.0019, 0.0013, 0.0082, -0.0001, -0.0002, 0.0053, 0.0000, 0.0053, 0.4218, 3.8796, 3.9836, 0.0762, 0.0762, -0.0242, -0.0177, 0.0137, 0.0243, -0.0016, -0.0010, 0.0167, 0.0003, 0.0167, 0.0523, -1.4181, 3.5591, 0.4571, 0.4952, -0.0043, -0.0005, 0.0004, 0.0037, -0.0001, -0.0001, 0.0021, 0.0000, 0.0021, -0.2167, 0.7137, 4.0117, 0.1238, 0.1238, -0.0033, -0.0022, 0.0018, 0.0042, 0.0000, 0.0001, 0.0024, 0.0000, 0.0024, 0.3726, -0.6343, 3.3716, 0.5143, 0.4952, -0.0008, -0.0001, 0.0001, 0.0007, -0.0000, 0.0000, 0.0004, 0.0000, 0.0004, 0.0392, 1.9287, 3.9401, 0.0762, 0.0952, -0.0083, -0.0032, 0.0044, 0.0075, 0.0000, 0.0002, 0.0050, 0.0000, 0.0050, -0.2188, -0.5759, 3.2805, 0.4952, 0.4762, -0.0013, -0.0001, 0.0001, 0.0011, 0.0000, -0.0000, 0.0006, 0.0000, 0.0006, -0.4832, 2.1682
};

/**
 * @brief      Copy raw feature data in out_ptr
 *             Function called by inference library
 *
 * @param[in]  offset   The offset
 * @param[in]  length   The length
 * @param      out_ptr  The out pointer
 *
 * @return     0
 */
int raw_feature_get_data(size_t offset, size_t length, float *out_ptr) {
    memcpy(out_ptr, features + offset, length * sizeof(float));
    return 0;
}

void print_inference_result(ei_impulse_result_t result);

/**
 * @brief      Arduino setup function
 */
void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    // comment out the below line to cancel the wait for USB connection (needed for native USB)
    while (!Serial);
    Serial.println("Edge Impulse Inferencing Demo");
}

/**
 * @brief      Arduino main function
 */
void loop()
{
    ei_printf("Edge Impulse standalone inferencing (Arduino)\n");

    if (sizeof(features) / sizeof(float) != EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE) {
        ei_printf("The size of your 'features' array is not correct. Expected %lu items, but had %lu\n",
            EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, sizeof(features) / sizeof(float));
        delay(1000);
        return;
    }

    ei_impulse_result_t result = { 0 };

    // the features are stored into flash, and we don't want to load everything into RAM
    signal_t features_signal;
    features_signal.total_length = sizeof(features) / sizeof(features[0]);
    features_signal.get_data = &raw_feature_get_data;

    // invoke the impulse
    EI_IMPULSE_ERROR res = run_classifier(&features_signal, &result, false /* debug */);
    if (res != EI_IMPULSE_OK) {
        ei_printf("ERR: Failed to run classifier (%d)\n", res);
        return;
    }

    // print inference return code
    ei_printf("run_classifier returned: %d\r\n", res);
    print_inference_result(result);

    delay(1000);
}

void print_inference_result(ei_impulse_result_t result) {

    // Print how long it took to perform inference
    ei_printf("Timing: DSP %d ms, inference %d ms, anomaly %d ms\r\n",
            result.timing.dsp,
            result.timing.classification,
            result.timing.anomaly);

    // Print the prediction results (object detection)
#if EI_CLASSIFIER_OBJECT_DETECTION == 1
    ei_printf("Object detection bounding boxes:\r\n");
    for (uint32_t i = 0; i < result.bounding_boxes_count; i++) {
        ei_impulse_result_bounding_box_t bb = result.bounding_boxes[i];
        if (bb.value == 0) {
            continue;
        }
        ei_printf("  %s (%f) [ x: %u, y: %u, width: %u, height: %u ]\r\n",
                bb.label,
                bb.value,
                bb.x,
                bb.y,
                bb.width,
                bb.height);
    }

    // Print the prediction results (classification)
#else
    ei_printf("Predictions:\r\n");
    for (uint16_t i = 0; i < EI_CLASSIFIER_LABEL_COUNT; i++) {
        ei_printf("  %s: ", ei_classifier_inferencing_categories[i]);
        ei_printf("%.5f\r\n", result.classification[i].value);
    }
#endif

    // Print anomaly result (if it exists)
#if EI_CLASSIFIER_HAS_ANOMALY == 1
    ei_printf("Anomaly prediction: %.3f\r\n", result.anomaly);
#endif

}