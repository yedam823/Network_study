from ultralytics import YOLO
import glob
import random
import os
from IPython.display import Image, display

# 방금 학습 끝난 버전의 최고 가중치 파일 불러오기
model_path = "/content/runs/detect/firmware_tank_tracker/v2_tank_augmented/weights/best.pt"
model = YOLO(model_path)

# 다운받은 데이터셋의 test 폴더에서 무작위로 사진 한 장 고르기
test_images = glob.glob(f"{dataset.location}/test/images/*.jpg")
test_img = random.choice(test_images)

# 3. 예측(추론) 실행 
# conf=0.5 (50% 이상 확신할 때만 타겟으로 인정)
results = model.predict(source=test_img, save=True, conf=0.5, project="firmware_tank_tracker", name="v2_test_result")

# 4. 타겟 좌표(X, Y) 추출하기
print("\n" + "═"*50)
for r in results:
    boxes = r.boxes
    if len(boxes) == 0:
        print("🤷‍♂️ 이 사진에서는 탱크를 찾지 못했습니다. (다른 사진으로 다시 실행해보세요!)")
    
    for box in boxes:
        # xywh = 중심 X, 중심 Y, 너비, 높이
        x, y, w, h = box.xywh[0]
        print(f"🎯 펌웨어 전송용 타겟 좌표 추출! ➔ X: {int(x)}, Y: {int(y)}")
print("═"*50 + "\n")

# 5. 결과 사진을 코랩 화면에 바로 띄우기
result_img_path = os.path.join(results[0].save_dir, os.path.basename(test_img))
display(Image(filename=result_img_path))
