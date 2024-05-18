.PHONY: build
.DEFAULT_GOAL := help

ROOT_DIR=${PWD}

PROJ=axmol-native-helper

help:
	@echo "Type: make [rule]. Available options are:"
	@echo ""
	@echo "- help"
	@echo "- format"
	@echo "- clean"
	@echo ""
	@echo "- build-ios"
	@echo "- build-tvos"
	@echo "- build-macos"
	@echo "- build-wasm"
	@echo ""
	@echo "- deploy-ios"
	@echo "- deploy-tvos"
	@echo "- deploy-android"
	@echo ""

format:
	find -E Source/ -not -path '*/vendor/*' -regex '.*\.(cpp|hpp|cc|cxx|c|h)' -exec clang-format -style=file -i {} \;
	find -E Platform/ -regex '.*\.(cpp|hpp|cc|cxx|c|h)' -exec clang-format -style=file -i {} \;

clean:
	rm -rf build_*
	rm -rf proj.android/app/build
	find . -name ".DS_Store" -delete

build-ios:
	rm -rf build_ios_arm64/
	axmol build -p ios -a arm64 -c

build-tvos:
	rm -rf build_tvos_arm64/
	axmol build -p tvos -a arm64 -c

build-macos:
	rm -rf build_arm64/
	axmol build -c

build-wasm:
	rm -rf build_wasm/
	axmol build -p wasm
	cd build_wasm && make
	cp build_wasm/bin/${PROJ}/${PROJ}.html build_wasm/bin/${PROJ}/index.html

deploy-ios:
	rm -rf build_ios_arm64/
	axmol build -p ios -a arm64 -c

	cd build_ios_arm64 && \
		xcodebuild -workspace ${PROJ}.xcworkspace -scheme ${PROJ} -sdk iphoneos

	cd build_ios_arm64 && \
		xcodebuild archive -workspace ${PROJ}.xcworkspace -scheme ${PROJ} -archivePath ${PROJ}.xcarchive

	cd build_ios_arm64 && \
		xcodebuild -exportArchive -archivePath ${PROJ}.xcarchive -allowProvisioningUpdates -exportOptionsPlist ../proj.ios_mac/ios/exportoptions-prod.plist -exportPath .

	cd build_ios_arm64 && \
		xcrun altool --upload-app -f ${PROJ}.ipa -t ios -u paulocoutinhox@gmail.com -p ${APPLE_SPECIFIC_PASSWORD}

deploy-tvos:
	rm -rf build_tvos_arm64/
	axmol build -p tvos -a arm64 -c

	cd build_tvos_arm64 && \
		xcodebuild -workspace ${PROJ}.xcworkspace -scheme ${PROJ} -sdk appletvos

	cd build_tvos_arm64 && \
		xcodebuild archive -workspace ${PROJ}.xcworkspace -scheme ${PROJ} -archivePath ${PROJ}.xcarchive

	cd build_tvos_arm64 && \
		xcodebuild -exportArchive -archivePath ${PROJ}.xcarchive -allowProvisioningUpdates -exportOptionsPlist ../proj.ios_mac/ios/exportoptions-prod.plist -exportPath .

	cd build_tvos_arm64 && \
		xcrun altool --upload-app -f ${PROJ}.ipa -t tvos -u paulocoutinhox@gmail.com -p ${APPLE_SPECIFIC_PASSWORD}

deploy-android:
	cd proj.android && ./gradlew clean bundleRelease
	echo "The bundle is here: proj.android/app/build/outputs/bundle/release/${PROJ}-release.aab"
