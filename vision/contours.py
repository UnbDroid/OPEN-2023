import cv2
import numpy as np

def find_contours(frame):
    # Convert the frame to grayscale
    gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    
    # Apply Gaussian blur to reduce noise
    blurred_frame = cv2.GaussianBlur(gray_frame, (5, 5), 0)
    
    # Use the Canny edge detection algorithm to get the edges
    edges = cv2.Canny(blurred_frame, threshold1=30, threshold2=100)

    # Find contours in the edge-detected image
    all_contours, _ = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    return all_contours

def find_contours2(frame, canny_threshold1=30, canny_threshold2=100):
    # Convert the frame to grayscale
    gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    
    # Apply Gaussian blur to reduce noise
    blurred_frame = cv2.GaussianBlur(gray_frame, (5, 5), 0)
    
    # Use the Canny edge detection algorithm to get the edges
    edges = cv2.Canny(blurred_frame, threshold1=canny_threshold1, threshold2=canny_threshold2)

    # Find contours in the edge-detected image
    all_contours, _ = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # Filter contours based on area and aspect ratio
    filtered_contours = []
    for contour in all_contours:
        area = cv2.contourArea(contour)
        x, y, w, h = cv2.boundingRect(contour)
        aspect_ratio = w / h
        
        if area >= 10 and 0.5 <= aspect_ratio <= 2:
            filtered_contours.append(contour)

    return filtered_contours


def draw_contours(frame, contours):
    frame_with_contours = frame.copy()
    
    colors = [(255,0,0), (0,255,0), (0,0,255)]
    for i, contour in enumerate(contours):
        color =  (4,23,123)
        cv2.drawContours(frame_with_contours, [contour], -1, color, 2)
    
    return frame_with_contours

def draw_contours_with_name(frame, contours, color_names):
    frame_with_contours = frame.copy()
    
    colors = [(255, 0, 0), (0, 255, 0), (0, 0, 255)]
    for i, contour in enumerate(contours):
        color = (4,23,123)  # Generate a color for each contour
        cv2.drawContours(frame_with_contours, [contour], -1, color, 2)

        # Get the bounding box of the contour
        x, y, w, h = cv2.boundingRect(contour)

        # Choose a font and position for the text
        font = cv2.FONT_HERSHEY_SIMPLEX
        font_scale = 0.7
        font_thickness = 2
        text_color = (255, 255, 255)  # White color for the text
        text_x = x + int(w / 2) - 30
        text_y = y + int(h / 2)

        # Get the color name for the current contour
        name = color_names[i]

        # Draw the text on the frame
        cv2.putText(frame_with_contours, name, (text_x, text_y), font, font_scale, text_color, font_thickness)

    cv2.imshow("Imagem Final", frame_with_contours)
    return frame_with_contours

def draw_specific_contours_with_name(frame, contours, color_names, num):
    frame_with_contours = frame.copy()
    
    colors = [(255, 0, 0), (0, 255, 0), (0, 0, 255)]
    for i, contour in enumerate(contours):
        if i == num-1:
            color = (4,23,123)  # Generate a color for each contour
            cv2.drawContours(frame_with_contours, [contour], -1, color, 2)

            # Get the bounding box of the contour
            x, y, w, h = cv2.boundingRect(contour)

            # Choose a font and position for the text
            font = cv2.FONT_HERSHEY_SIMPLEX
            font_scale = 0.7
            font_thickness = 2
            text_color = (255, 255, 255)  # White color for the text
            text_x = x + int(w / 2) - 30
            text_y = y + int(h / 2)

            # Get the color name for the current contour
            name = color_names[i]

            # Draw the text on the frame
            cv2.putText(frame_with_contours, name, (text_x, text_y), font, font_scale, text_color, font_thickness)
            cv2.imshow("Imagem Final", frame_with_contours)
            return frame_with_contours


def print_contour_properties(contours):
    for contour in contours:
        area = cv2.contourArea(contour)
        num_sides = len(cv2.approxPolyDP(contour, 0.03 * cv2.arcLength(contour, True), True))
        num_corners = len(cv2.convexHull(contour, clockwise=False, returnPoints=False))
        convexity = cv2.isContourConvex(contour)
        x, y, w, h = cv2.boundingRect(contour)
        compactness = (w * h) / (area + 1e-5)
        extent = area / (w * h + 1e-5)
        hull_area = cv2.contourArea(cv2.convexHull(contour))
        solidity = area / (hull_area + 1e-5)
        # orientation = cv2.fitEllipse(contour)[2]
        rectangularity = area / (w * h + 1e-5)
        circularity = (4 * np.pi * area) / (cv2.arcLength(contour, True) ** 2 + 1e-5)
        euler_number = num_corners - num_sides

        # Create a single string with all the properties
        properties_str = f"Contour properties: Area: {area:.2f}, Sides: {num_sides}, Corners: {num_corners}, Convexity: {convexity}, Bounding Rectangle (w, h): {w}, {h}, Compactness: {compactness:.5f}, Extent: {extent:.5f}, Solidity: {solidity:.5f}, Rectangularity: {rectangularity:.5f}, Circularity: {circularity:.5f}, Euler's Number: {euler_number}"

        # Print the single string containing all properties
        print(properties_str)

def print_less_contour_properties(contours):
    for i, contour in enumerate(contours):
        area = cv2.contourArea(contour)
        num_sides = len(cv2.approxPolyDP(contour, 0.03 * cv2.arcLength(contour, True), True))
        num_corners = len(cv2.convexHull(contour, clockwise=False, returnPoints=False))
        convexity = cv2.isContourConvex(contour)
        x, y, w, h = cv2.boundingRect(contour)
        compactness = (w * h) / (area + 1e-5)
        extent = area / (w * h + 1e-5)
        hull_area = cv2.contourArea(cv2.convexHull(contour))
        solidity = area / (hull_area + 1e-5)
        # orientation = cv2.fitEllipse(contour)[2]
        rectangularity = area / (w * h + 1e-5)
        circularity = (4 * np.pi * area) / (cv2.arcLength(contour, True) ** 2 + 1e-5)
        euler_number = num_corners - num_sides

        # Create a single string with all the properties
        properties_str = f"Contour {i+1} properties: Area: {area:.2f}, Sides: {num_sides}, Corners: {num_corners}, w: {w}, h: {h}"

        # Print the single string containing all properties
        print(properties_str)
def get_median_bgr_hsv_inside_contours(frame, contours):
    # Convert the frame to HSV color space
    hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    median_bgr_values = []
    median_hsv_values = []

    for contour in contours:
        # Create a mask for the current contour
        mask = np.zeros(frame.shape[:2], dtype=np.uint8)
        cv2.drawContours(mask, [contour], -1, 255, thickness=cv2.FILLED)

        # Extract the pixels inside the contour using the mask
        pixels_inside_contour = frame[np.where(mask)]
        hsv_pixels_inside_contour = hsv_frame[np.where(mask)]

        # Calculate the median BGR values of the pixels inside the contour
        median_bgr = np.median(pixels_inside_contour, axis=0)
        median_bgr_values.append(median_bgr)

        # Calculate the median HSV values of the pixels inside the contour
        median_hsv = np.median(hsv_pixels_inside_contour, axis=0)
        median_hsv_values.append(median_hsv)

    return median_bgr_values, median_hsv_values