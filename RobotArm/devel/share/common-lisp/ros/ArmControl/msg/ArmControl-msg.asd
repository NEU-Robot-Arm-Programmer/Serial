
(cl:in-package :asdf)

(defsystem "ArmControl-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "angle_msg" :depends-on ("_package_angle_msg"))
    (:file "_package_angle_msg" :depends-on ("_package"))
  ))