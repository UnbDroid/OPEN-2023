from contours import *

def detect_color(image):
    all_contours = find_contours(image)
    contours = [contour for contour in all_contours if len(cv2.approxPolyDP(contour, 0.03 * cv2.arcLength(contour, True), True)) >= 6 and cv2.contourArea(contour) >= 10]
    median_bgr_values, median_hsv_values = get_median_bgr_hsv_inside_contours(image, contours)
    color_name = [""]* len(contours)
    # Print the median BGR and HSV values for each contour

    for i, (bgr_values, hsv_values) in enumerate(zip(median_bgr_values, median_hsv_values)):
        # print(f"Contour {i + 1}: Median BGR = {bgr_values}, Median HSV = {hsv_values}")
        # if bgr_values[2] > (((bgr_values[0] + bgr_values[1])/2) + 20):
        #     color_name[i] = "Vermelho"
        color_name[i] = f"{i + 1}"
    
    frame_with_contours = draw_contours_with_name(image,contours, color_name)
    return frame_with_contours



# image = cv2.imread("vision/cubes.png")
# final_image = detect_color(image)
# cv2.imshow("Imagem Final", final_image)
# cv2.waitKey(0)