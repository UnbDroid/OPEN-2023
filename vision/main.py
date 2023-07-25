import cv2
import numpy as np
import time

def get_central_pixel_bgr(frame):
    height, width, _ = frame.shape
    center_y, center_x = height // 2, width // 2
    bgr = frame[center_y, center_x]
    return bgr

def draw_circle_on_pixel(frame, center_coordinates):
    radius = 5
    color = (0, 0, 255)  # Red color in BGR format (OpenCV uses BGR instead of RGB)
    thickness = 2
    frame_copy = frame.copy()
    cv2.circle(frame_copy, center_coordinates, radius, color, thickness)
    return frame_copy


def write_bgr_on_screen(frame, bgr_values):
        # Display the RGB values on the screen
        font = cv2.FONT_HERSHEY_SIMPLEX
        font_scale = 0.7
        font_color = (255, 255, 255)  # White color in BGR format
        thickness = 2
        text = f"BGR: {bgr_values}"
        text_size = cv2.getTextSize(text, font, font_scale, thickness)[0]
        text_position = ((frame.shape[1] - text_size[0]) // 2, 50)
        cv2.putText(frame, text, text_position, font, font_scale, font_color, thickness)


def show_red_part_only(frame):
    lower_red = np.array([0, 0, 40])    # Lower bound of red color in BGR
    upper_red = np.array([5, 5, 255])  # Upper bound of red color in BGR
    mask = cv2.inRange(frame, lower_red, upper_red)
    red_part = cv2.bitwise_and(frame, frame, mask=mask)
    return red_part

def show_green_part_only(frame):
    lower_green = np.array([0, 100, 0])    # Lower bound of green color in BGR
    upper_green = np.array([50, 255, 50])  # Upper bound of green color in BGR
    mask = cv2.inRange(frame, lower_green, upper_green)
    green_part = cv2.bitwise_and(frame, frame, mask=mask)
    return green_part

def show_blue_part_only(frame):
    lower_blue = np.array([30, 0, 0])    # Lower bound of blue color in BGR
    upper_blue = np.array([255, 10, 10])  # Upper bound of blue color in BGR
    mask = cv2.inRange(frame, lower_blue, upper_blue)
    blue_part = cv2.bitwise_and(frame, frame, mask=mask)
    return blue_part

def show_yellow_part_only(frame):
    lower_yellow = np.array([0, 70, 70])    # Lower bound of yellow color in BGR
    upper_yellow = np.array([50, 255, 255])   # Upper bound of yellow color in BGR
    mask = cv2.inRange(frame, lower_yellow, upper_yellow)
    yellow_part = cv2.bitwise_and(frame, frame, mask=mask)
    return yellow_part

def show_all_frames(frame):
    # yellow = show_yellow_part_only(frame)
    # cv2.imshow('Yellow', yellow)

    # blue = show_blue_part_only(frame)
    # cv2.imshow('Blue', blue)

    # green = show_green_part_only(frame)
    # cv2.imshow('Green', green)

    red = show_red_part_only(frame)
    cv2.imshow('Red', red)

def calculate_percentages(frame):
    total_pixels = frame.shape[0] * frame.shape[1]

    red = show_red_part_only(frame)
    red_pixels = np.sum(np.all(red > 0, axis=-1))

    green = show_green_part_only(frame)
    green_pixels = np.sum(np.all(green > 0, axis=-1))

    blue = show_blue_part_only(frame)
    blue_pixels = np.sum(np.all(blue > 0, axis=-1))

    yellow = show_yellow_part_only(frame)
    yellow_pixels = np.sum(np.all(yellow > 0, axis=-1))

    red_percentage = (red_pixels / total_pixels) * 100
    green_percentage = (green_pixels / total_pixels) * 100
    blue_percentage = (blue_pixels / total_pixels) * 100
    yellow_percentage = (yellow_pixels / total_pixels) * 100
    # print(red_percentage)
    # if red_percentage >= 0.02:
    #     print("Cubo Vermelho")
    # else:
    #     print("Nenhum Cubo")

    return red_percentage, green_percentage, blue_percentage, yellow_percentage

def detect_red_cube(frame):
    # Converter o frame para o espaço de cores HSV
    hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # Definir as faixas de cores para a cor vermelha em HSV
    lower_red = np.array([0, 100, 100])
    upper_red = np.array([10, 255, 255])
    mask1 = cv2.inRange(hsv_frame, lower_red, upper_red)

    lower_red = np.array([160, 100, 100])
    upper_red = np.array([179, 255, 255])
    mask2 = cv2.inRange(hsv_frame, lower_red, upper_red)

    # Combinar as máscaras para obter a máscara final
    red_mask = mask1 + mask2

    # Aplicar detecção de bordas usando o método Canny
    edges = cv2.Canny(red_mask, 50, 150)

    # Encontrar os contornos dos objetos detectados
    contours, _ = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # Verificar se há pelo menos um contorno significativo (ajuste o valor conforme necessário)
    for contour in contours:
        perimeter = cv2.arcLength(contour, True)
        if perimeter > 50:  # Ignorar contornos muito pequenos (ajuste esse valor conforme necessário)
            return True

    return False


def main():
    cap = cv2.VideoCapture(0)

    while True:
        ret, frame = cap.read()

        if not ret:
            break

        # Get the RGB values of the central pixel
        center_pixel_bgr = get_central_pixel_bgr(frame)

        calculate_percentages(frame)
        print(detect_red_cube(frame))

        show_all_frames(frame)
        # Write the BGR values of the middle pixel on the screen
        write_bgr_on_screen(frame, center_pixel_bgr)

        # Draw a red circle on the central pixel
        frame_with_circle = draw_circle_on_pixel(frame, (frame.shape[1] // 2, frame.shape[0] // 2))



        # Show the frame with the circle on the central pixel
        cv2.imshow('Video', frame_with_circle)

        # Exit when 'q' is pressed
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()


if __name__ == "__main__":
    main()
