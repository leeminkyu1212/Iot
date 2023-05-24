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
    // copy raw features here (for example from the 'Live classification' page)
    // see https://docs.edgeimpulse.com/docs/running-your-impulse-arduino
    4.0332, 0.1333, 0.1333, -0.0100, -0.0033, 0.0040, 0.0087, -0.0007, -0.0002, 0.0054, 0.0000, 0.0054, -0.0634, -0.5226, 3.7983, 0.5905, 0.6095, -0.0005, -0.0001, 0.0003, 0.0007, 0.0001, 0.0001, 0.0003, 0.0000, 0.0004, -0.1867, 0.3741, 3.0003, 0.1143, 0.1143, -0.0400, -0.0175, 0.0187, 0.0190, 0.0131, 0.0007, 0.0218, 0.0005, 0.0218, -0.8309, -0.8844, 3.6043, 0.6476, 0.7048, -0.0019, -0.0007, 0.0004, 0.0023, 0.0000, 0.0000, 0.0012, 0.0000, 0.0012, 0.5661, 0.7990, 3.4464, 0.1238, 0.1238, -0.0321, -0.0242, 0.0266, 0.0296, 0.0003, 0.0001, 0.0239, 0.0006, 0.0239, -0.0833, -1.5938, 3.5532, 0.6762, 0.6762, -0.0016, -0.0005, 0.0005, 0.0016, 0.0000, -0.0000, 0.0010, 0.0000, 0.0010, -0.4808, 3.2930, 3.8987, 0.1619, 0.1619, -0.1304, -0.0479, 0.0609, 0.1154, -0.0148, -0.0003, 0.0726, 0.0053, 0.0726, 0.1593, -0.4386, 3.4480, 0.6476, 0.6667, -0.0151, -0.0042, 0.0027, 0.0114, 0.0001, -0.0004, 0.0092, 0.0001, 0.0092, 0.1607, 3.7843, 3.9648, 0.1143, 0.1143, -0.4325, -0.2882, 0.3211, 0.4486, 0.0478, 0.0104, 0.3250, 0.1066, 0.3252, -0.0046, -1.4835, 3.7221, 0.5905, 0.5524, -0.0225, -0.0062, 0.0062, 0.0207, -0.0000, -0.0002, 0.0127, 0.0002, 0.0127, -0.0969, 1.4750, 4.0507, 0.1238, 0.1238, -0.4549, -0.3520, 0.3756, 0.5525, -0.0517, 0.0022, 0.3700, 0.1382, 0.3700, 0.2040, -1.4473, 3.5154, 0.6190, 0.6000, -0.0266, -0.0065, 0.0051, 0.0292, 0.0012, -0.0002, 0.0150, 0.0002, 0.0150, 0.3382, 2.3110, 4.1488, 0.1333, 0.1333, -0.0124, -0.0069, 0.0069, 0.0107, -0.0010, -0.0003, 0.0076, 0.0001, 0.0076, -0.0992, -1.2376, 3.5683, 0.4857, 0.4476, -0.0028, -0.0005, 0.0003, 0.0032, -0.0001, 0.0000, 0.0015, 0.0000, 0.0015, 0.3357, 0.8732, 4.0035, 0.1524, 0.1524, -0.0132, -0.0098, 0.0093, 0.0158, -0.0026, -0.0004, 0.0100, 0.0001, 0.0100, 0.3514, -1.2574, 3.4609, 0.4476, 0.4476, -0.0030, -0.0007, 0.0003, 0.0042, -0.0001, 0.0000, 0.0020, 0.0000, 0.0020, 0.6396, 1.0191, 4.1042, 0.1238, 0.1429, -0.0110, -0.0060, 0.0068, 0.0111, -0.0008, -0.0001, 0.0074, 0.0001, 0.0074, 0.0848, -1.1339, 3.5954, 0.4952, 0.4762, -0.0024, -0.0005, 0.0003, 0.0030, -0.0001, 0.0000, 0.0015, 0.0000, 0.0015, 0.3700, 0.5492
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