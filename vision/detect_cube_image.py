from contours import *


image = cv2.imread("vision/5cubes_2.png")
all_contours = find_contours2(image)
contours = all_contours
# contours = [contour for contour in all_contours if len(cv2.approxPolyDP(contour, 0.03 * cv2.arcLength(contour, True), True)) >= 5 
#             and cv2.contourArea(contour) >= 10
#             and 0.5 <= cv2.boundingRect(contour)[2] / cv2.boundingRect(contour)[3] <= 2]

print_less_contour_properties(contours)

median_bgr_values, median_hsv_values = get_median_bgr_hsv_inside_contours(image, contours)

color_name = [""]* len(contours)
# Print the median BGR and HSV values for each contour
for i, (bgr_values, hsv_values) in enumerate(zip(median_bgr_values, median_hsv_values)):
    # print(f"Contour {i + 1}: Median BGR = {bgr_values}, Median HSV = {hsv_values}")
    color_name[i] = f"{i + 1}"
    # if bgr_values[2] > (((bgr_values[0] + bgr_values[1])/2) + 20):
    #     color_name[i] = "Vermelho"

for i in range(len(contours)+1):
    draw_specific_contours_with_name(image, contours, color_name, i)
    cv2.waitKey(0)

draw_contours_with_name(image, contours, color_name)
cv2.waitKey(0)

