from PIL import Image

# Open an image file
with Image.open('utils/img.jpg') as img:
    # Resize image
    new_size = (64, 64)  # Replace with desired width and height
    resized_img = img.resize(new_size, Image.Resampling.LANCZOS)

    # Save the resized image
    resized_img.save('utils/img.jpg')
