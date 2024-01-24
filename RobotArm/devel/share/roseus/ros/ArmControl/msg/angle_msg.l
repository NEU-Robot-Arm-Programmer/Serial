;; Auto-generated. Do not edit!


(when (boundp 'ArmControl::angle_msg)
  (if (not (find-package "ARMCONTROL"))
    (make-package "ARMCONTROL"))
  (shadow 'angle_msg (find-package "ARMCONTROL")))
(unless (find-package "ARMCONTROL::ANGLE_MSG")
  (make-package "ARMCONTROL::ANGLE_MSG"))

(in-package "ROS")
;;//! \htmlinclude angle_msg.msg.html


(defclass ArmControl::angle_msg
  :super ros::object
  :slots (_angles ))

(defmethod ArmControl::angle_msg
  (:init
   (&key
    ((:angles __angles) 0.0)
    )
   (send-super :init)
   (setq _angles (float __angles))
   self)
  (:angles
   (&optional __angles)
   (if __angles (setq _angles __angles)) _angles)
  (:serialization-length
   ()
   (+
    ;; float64 _angles
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _angles
       (sys::poke _angles (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _angles
     (setq _angles (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get ArmControl::angle_msg :md5sum-) "22b07857a56aae829de3d30b31b536a0")
(setf (get ArmControl::angle_msg :datatype-) "ArmControl/angle_msg")
(setf (get ArmControl::angle_msg :definition-)
      "float64 angles
")



(provide :ArmControl/angle_msg "22b07857a56aae829de3d30b31b536a0")


